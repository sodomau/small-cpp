param(
    [string]$BuildDir = "",
    [string]$OutputDir = "",
    [string]$NoticesDir = "",
    [string]$Msys2Dir = ""
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

if ([string]::IsNullOrWhiteSpace($Msys2Dir)) {
    throw "Pass -Msys2Dir with an initialized MSYS2/UCRT64 environment."
}
$Msys2Dir = (Resolve-Path -LiteralPath $Msys2Dir).Path
$environmentCompiler = Join-Path $Msys2Dir 'ucrt64/bin/g++.exe'
if (!(Test-Path -LiteralPath $environmentCompiler)) { throw 'Missing UCRT64 compiler.' }
$builtVersion = $kv['compiler_version']
$environmentVersion = & $environmentCompiler -dumpfullversion
if ($LASTEXITCODE -ne 0 -or [string]::IsNullOrWhiteSpace($builtVersion) -or $builtVersion -ne $environmentVersion) {
    throw 'Build the IDE/runtime with the same UCRT64 compiler version as the packaged environment.'
}

$compilerBin = Split-Path $compiler -Parent
$deploy = Join-Path $qtBin "windeployqt.exe"
$env:PATH = "$compilerBin;$qtBin;" + $env:PATH

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
$publicDocs = @('GETTING_STARTED.md', 'SMALL_CPP_GUIDE.md', 'API.md', 'DESIGN.md', 'TUTORIAL_ENGLISH.md', 'PROJECT_MODE.md', 'PUBLISH.md', 'NAMING_CONVENTIONS.md', 'WINDOWS_INSTALLATION.md', 'MSYS2_ENVIRONMENT.md')
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

# windeployqt handles Qt, but not the editor's KDE/non-Qt DLL imports.
$dependencyCollector = Join-Path $repoRoot 'tools\deploy_editor_dependencies.py'
$pythonCommand = Get-Command python -ErrorAction SilentlyContinue
if (!$pythonCommand) { throw 'Python is required to collect editor dependencies.' }
& $pythonCommand.Source $dependencyCollector --package $OutputDir --prefix (Split-Path $qtBin -Parent) --objdump (Join-Path $compilerBin 'objdump.exe')
if ($LASTEXITCODE -ne 0) { throw 'Editor dependency collection failed.' }

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

# Keep the package manager and its databases with the UCRT64 toolchain.
$environmentOut = Join-Path $OutputDir "env"
& $pythonCommand.Source (Join-Path $repoRoot 'tools/copy_msys2_environment.py') --source $Msys2Dir --destination $environmentOut --minimal
if ($LASTEXITCODE -ne 0) { throw 'MSYS2 environment copy failed.' }
# The compiler's newer runtime must accompany student executables, including
# Publish output. Qt/KDE must come from a matching UCRT64 build kit.
foreach ($dll in @("libwinpthread-1.dll", "libgcc_s_seh-1.dll", "libstdc++-6.dll")) {
    $candidate = Join-Path $environmentOut ("ucrt64/bin/" + $dll)
    if (!(Test-Path $candidate)) { throw "Missing UCRT64 runtime: $candidate" }
    Copy-Item -LiteralPath $candidate -Destination (Join-Path $OutputDir $dll) -Force
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
