param(
    [string]$BuildDir = "",
    [string]$OutputDir = ""
)

$ErrorActionPreference = "Stop"

if ([string]::IsNullOrWhiteSpace($BuildDir)) {
    $repoRoot = (Resolve-Path (Join-Path $PSScriptRoot "..")).Path
    $candidates = @(
        Get-ChildItem (Join-Path $repoRoot "ide\build") -Directory -ErrorAction SilentlyContinue |
        Where-Object { $_.Name -match "_Release$" } |
        ForEach-Object { Join-Path $_.FullName "bin\Release" } |
        Where-Object { Test-Path (Join-Path $_ "SmallCppIDE.exe") }
    )

    if ($candidates.Count -eq 0) {
        throw "Release build not found. Build the Release configuration in Qt Creator first."
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

Remove-Item $OutputDir -Recurse -Force -ErrorAction SilentlyContinue
New-Item -ItemType Directory -Path $OutputDir | Out-Null

# Copy only Small-owned build artifacts.
Copy-Item $exe (Join-Path $OutputDir "SmallCppIDE.exe") -Force
Copy-Item $runtime (Join-Path $OutputDir "runtime") -Recurse -Force
Copy-Item $extensions (Join-Path $OutputDir "extensions") -Recurse -Force
Copy-Item $tutorial (Join-Path $OutputDir "tutorial") -Recurse -Force

# Deploy Qt runtime and plugins from both dependency roots.
# SmallCppIDE does not itself use every Qt module used by learner programs.
Copy-Item $deployProbe (Join-Path $OutputDir "SmallDeployProbe.exe") -Force

& $deploy --release --compiler-runtime --dir $OutputDir (Join-Path $OutputDir "SmallCppIDE.exe")
if ($LASTEXITCODE -ne 0) {
    throw "windeployqt failed for SmallCppIDE.exe (exit code $LASTEXITCODE)"
}

& $deploy --release --compiler-runtime --dir $OutputDir (Join-Path $OutputDir "SmallDeployProbe.exe")
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
Write-Host "Portable Small C++ created:"
Write-Host "  $OutputDir"
Write-Host ""
Write-Host "Next test:"
Write-Host "  Copy this folder to a Windows PC without Qt/MinGW installed,"
Write-Host "  run SmallCppIDE.exe, then run Lesson 1 and an Image example."
