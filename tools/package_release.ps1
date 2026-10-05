param(
    [string]$BuildDir = "",
    [string]$OutputDir = "",
    [string]$NoticesDir = ""
)

$ErrorActionPreference = "Stop"
$repoRoot = (Resolve-Path (Join-Path $PSScriptRoot "..")).Path

if ([string]::IsNullOrWhiteSpace($BuildDir)) {
    $candidates = @(
        Get-ChildItem (Join-Path $repoRoot "build") -Directory -ErrorAction SilentlyContinue |
        ForEach-Object { Join-Path $_.FullName "bin\Release" } |
        Where-Object { Test-Path (Join-Path $_ "SmallCppIDE.exe") }
    )

    if ($candidates.Count -eq 0) {
        throw "Release build not found under build/. Pass -BuildDir explicitly."
    }
    if ($candidates.Count -gt 1) {
        throw "More than one Release build was found. Pass -BuildDir explicitly."
    }
    $BuildDir = $candidates[0]
}

$build = (Resolve-Path $BuildDir).Path

if ([string]::IsNullOrWhiteSpace($OutputDir)) {
    # Keep destination outside BuildDir so packaging can never copy itself.
    $OutputDir = Join-Path (Split-Path $build -Parent) "SmallCpp-Portable"
}
$OutputDir = [System.IO.Path]::GetFullPath($OutputDir)
$allowedOutputRoot = [System.IO.Path]::GetFullPath((Join-Path $repoRoot 'build')) + [System.IO.Path]::DirectorySeparatorChar
if (!$OutputDir.StartsWith($allowedOutputRoot, [System.StringComparison]::OrdinalIgnoreCase)) {
    throw "OutputDir must be a subdirectory of the repository's build/ directory."
}
if ([string]::IsNullOrWhiteSpace($NoticesDir) -or !(Test-Path (Join-Path $NoticesDir 'THIRD_PARTY.txt')) -or
    !(Test-Path (Join-Path $NoticesDir 'SOURCE_ACCESS.md'))) {
    throw "Pass -NoticesDir with reviewed licenses, THIRD_PARTY.txt and SOURCE_ACCESS.md before packaging."
}

if ($OutputDir.StartsWith($build + [System.IO.Path]::DirectorySeparatorChar,
                          [System.StringComparison]::OrdinalIgnoreCase)) {
    throw "OutputDir must not be inside BuildDir."
}

$exe = Join-Path $build "SmallCppIDE.exe"
$deployProbe = Join-Path $build "SmallDeployProbe.exe"
$runtime = Join-Path $build "runtime"
$extensions = Join-Path $build "extensions"
$tutorial = Join-Path $build "tutorial"
$info = Join-Path $build "packaging-info.txt"

foreach ($required in @($exe, $deployProbe, $runtime, $extensions, $tutorial, $info)) {
    if (!(Test-Path $required)) {
        throw "Required Release artifact is missing: $required"
    }
}

$kv = @{}
Get-Content $info | ForEach-Object {
    $parts = $_ -split '=', 2
    if ($parts.Count -eq 2) { $kv[$parts[0]] = $parts[1] }
}

$compiler = $kv["compiler"]
$qtBin = $kv["qt_bin"]

if (!(Test-Path $compiler)) {
    throw "Recorded compiler does not exist: $compiler"
}

$compilerBin = Split-Path $compiler -Parent
$toolchainRoot = Split-Path $compilerBin -Parent
$deploy = Join-Path $qtBin "windeployqt.exe"

if (!(Test-Path $deploy)) {
    throw "windeployqt.exe was not found: $deploy"
}

if (Test-Path $OutputDir) {
    throw "OutputDir already exists. Use a fresh destination to preserve previous packages."
}
New-Item -ItemType Directory -Path $OutputDir | Out-Null

# Copy only Small-owned build artifacts.
Copy-Item $exe (Join-Path $OutputDir "SmallCppIDE.exe") -Force
Copy-Item $runtime (Join-Path $OutputDir "runtime") -Recurse -Force
Copy-Item $extensions (Join-Path $OutputDir "extensions") -Recurse -Force
Copy-Item $tutorial (Join-Path $OutputDir "tutorial") -Recurse -Force

# Keep learner documentation explicit; do not ship internal validation reports.
$publicDocs = @('GETTING_STARTED.md', 'SMALL_CPP_GUIDE.md', 'API.md', 'DESIGN.md', 'TUTORIAL_ENGLISH.md', 'PROJECT_MODE.md', 'PUBLISH.md', 'NAMING_CONVENTIONS.md', 'WINDOWS_INSTALLATION.md')
$docsOut = Join-Path $OutputDir 'docs'
New-Item -ItemType Directory -Path $docsOut | Out-Null
foreach ($doc in $publicDocs) {
    Copy-Item -LiteralPath (Join-Path $repoRoot "docs\$doc") -Destination (Join-Path $docsOut $doc)
}
Copy-Item -LiteralPath (Join-Path $repoRoot 'distribution\README.md') -Destination (Join-Path $OutputDir 'README.md')
Copy-Item -LiteralPath (Join-Path $repoRoot 'LICENSE') -Destination $OutputDir
Copy-Item -LiteralPath $NoticesDir -Destination (Join-Path $OutputDir 'licenses') -Recurse
Copy-Item -LiteralPath (Join-Path $repoRoot 'docs\PORTABLE_START.md') -Destination (Join-Path $OutputDir 'START_HERE.md')
New-Item -ItemType Directory -Path (Join-Path $OutputDir 'examples') | Out-Null
Copy-Item -LiteralPath (Join-Path $repoRoot 'examples\projects') -Destination (Join-Path $OutputDir 'examples\projects') -Recurse

# Deploy Qt runtime and plugins from both dependency roots.
# SmallCppIDE does not itself use every Qt module used by learner programs.
Copy-Item $deployProbe (Join-Path $OutputDir "SmallDeployProbe.exe") -Force

$deployOptions = @('--release', '--compiler-runtime', '--no-translations', '--no-opengl-sw',
                   '--no-system-d3d-compiler', '--no-ffmpeg', '--exclude-plugins', 'ffmpegmediaplugin', '--dir', $OutputDir)
& $deploy @deployOptions (Join-Path $OutputDir "SmallCppIDE.exe")
if ($LASTEXITCODE -ne 0) {
    throw "windeployqt failed for SmallCppIDE.exe (exit code $LASTEXITCODE)"
}

& $deploy @deployOptions (Join-Path $OutputDir "SmallDeployProbe.exe")
if ($LASTEXITCODE -ne 0) {
    throw "windeployqt failed for SmallDeployProbe.exe (exit code $LASTEXITCODE)"
}

Remove-Item (Join-Path $OutputDir "SmallDeployProbe.exe") -Force

foreach ($requiredRuntime in @(
    (Join-Path $OutputDir "Qt6Multimedia.dll"),
    (Join-Path $OutputDir "platforms\\qwindows.dll")
)) {
    if (!(Test-Path $requiredRuntime)) {
        throw "Learner Qt runtime deployment validation failed: $requiredRuntime"
    }
}

# Learner programs link against the precompiled Small runtime, which in turn
# needs the Qt import libraries. windeployqt copies runtime DLLs, not the
# developer/linker .a files, so copy the exact libraries recorded from the
# Qt kit used to build this release.
$portableQtLib = Join-Path $OutputDir "qt\lib"
New-Item -ItemType Directory -Path $portableQtLib -Force | Out-Null

foreach ($key in @("qt_widgets", "qt_gui", "qt_multimedia", "qt_core")) {
    $library = $kv[$key]
    if ([string]::IsNullOrWhiteSpace($library) -or !(Test-Path $library)) {
        throw "Qt linker library recorded for '$key' is missing: $library"
    }
    Copy-Item $library (Join-Path $portableQtLib (Split-Path $library -Leaf)) -Force
}

# MinGW contains a very deep header tree. PowerShell Copy-Item can fail on it;
# robocopy is substantially more robust for Windows toolchain directory trees.
$compilerOut = Join-Path $OutputDir "compiler"
New-Item -ItemType Directory -Path $compilerOut | Out-Null

Write-Host ""
Write-Host "Copying MinGW toolchain..."
& robocopy $toolchainRoot $compilerOut /E /COPY:DAT /DCOPY:DAT /R:2 /W:1 /NFL /NDL /NP

# Robocopy uses 0-7 for successful outcomes (including copied/skipped files).
$robocopyExit = $LASTEXITCODE
if ($robocopyExit -ge 8) {
    throw "robocopy failed while copying MinGW (exit code $robocopyExit)"
}

$bundled = Join-Path $compilerOut "bin\g++.exe"
if (!(Test-Path $bundled)) {
    throw "Bundled compiler validation failed: $bundled"
}

# Some Qt MinGW distributions keep GCC runtime DLLs under opt\bin while
# cc1plus.exe/gdb.exe are launched with compiler\bin on PATH. Copy the small
# runtime DLL set beside the tools so the portable compiler/debugger works on
# machines without a Qt installation.
$optBin = Join-Path $compilerOut "opt\bin"
$compilerBinOut = Join-Path $compilerOut "bin"
foreach ($dll in @("libwinpthread-1.dll", "libgcc_s_seh-1.dll", "libstdc++-6.dll")) {
    $candidate = Join-Path $optBin $dll
    if (Test-Path $candidate) { Copy-Item $candidate (Join-Path $compilerBinOut $dll) -Force }
}

$gdbBundled = Join-Path $compilerBinOut "gdb.exe"
if (!(Test-Path $gdbBundled)) {
    throw "Bundled debugger validation failed: $gdbBundled"
}

Write-Host ""
foreach ($key in @("qt_widgets", "qt_gui", "qt_multimedia", "qt_core")) {
    $name = Split-Path $kv[$key] -Leaf
    if (!(Test-Path (Join-Path $portableQtLib $name))) {
        throw "Portable Qt linker library validation failed: $name"
    }
}

Write-Host "Portable learner Qt runtime (windeployqt probe): OK"
Write-Host "Portable Qt linker libraries: OK"
foreach ($doc in $publicDocs) {
    if (!(Test-Path (Join-Path $docsOut $doc))) {
        throw "Packaged documentation validation failed: $doc"
    }
}
if (!(Test-Path (Join-Path $OutputDir 'README.md'))) {
    throw 'Packaged README validation failed.'
}
Write-Host "Portable documentation: OK"
Write-Host "Portable Small C++ created:"
Write-Host "  $OutputDir"
Write-Host ""
Write-Host "Next test:"
Write-Host "  Copy this folder to a Windows PC without Qt/MinGW installed,"
Write-Host "  run SmallCppIDE.exe, then run Lesson 1 and an Image example."
