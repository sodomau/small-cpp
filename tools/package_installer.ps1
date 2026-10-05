param(
    [Parameter(Mandatory = $true)][string]$PackageDir,
    [Parameter(Mandatory = $true)][string]$OutputDir,
    [string]$Compiler = ""
)

$ErrorActionPreference = 'Stop'
$repoRoot = (Resolve-Path (Join-Path $PSScriptRoot '..')).Path
$package = (Resolve-Path -LiteralPath $PackageDir).Path
$output = [System.IO.Path]::GetFullPath($OutputDir)
$buildRoot = [System.IO.Path]::GetFullPath((Join-Path $repoRoot 'build')) + [System.IO.Path]::DirectorySeparatorChar
if (!$output.StartsWith($buildRoot, [System.StringComparison]::OrdinalIgnoreCase)) {
    throw 'Installer output must be under build/.'
}
if ($output.Equals($package, [System.StringComparison]::OrdinalIgnoreCase) -or
    $output.StartsWith($package + [System.IO.Path]::DirectorySeparatorChar, [System.StringComparison]::OrdinalIgnoreCase)) {
    throw 'Installer output must not be inside the package.'
}
foreach ($relative in @('SmallCppIDE.exe', 'runtime\small.h', 'compiler\bin\g++.exe',
    'platforms\qwindows.dll', 'tutorial\01_hello\example.cpp', 'licenses\THIRD_PARTY.txt', 'licenses\SOURCE_ACCESS.md')) {
    if (!(Test-Path -LiteralPath (Join-Path $package $relative))) { throw "Incomplete portable package: $relative" }
}
$version = [System.Diagnostics.FileVersionInfo]::GetVersionInfo((Join-Path $package 'SmallCppIDE.exe')).ProductVersion
if ($version -notmatch '^\d+\.\d+\.\d+$') { throw 'Cannot read the IDE release version.' }
if ([string]::IsNullOrWhiteSpace($Compiler)) {
    $found = Get-Command ISCC.exe -ErrorAction SilentlyContinue
    if ($found) { $Compiler = $found.Source }
    else { throw 'Pass -Compiler with the path to the Inno Setup 6 or 7 ISCC.exe compiler.' }
}
$compilerPath = (Resolve-Path -LiteralPath $Compiler).Path
$destination = Join-Path $output "SmallCpp-v$version-Windows-x64-Setup.exe"
if (Test-Path -LiteralPath $destination) { throw 'Installer already exists; preserve it and choose a fresh output folder.' }
New-Item -ItemType Directory -Path $output -Force | Out-Null
& $compilerPath "/DPackageDir=$package" "/DOutputDir=$output" "/DAppVersion=$version" (Join-Path $repoRoot 'distribution\SmallCpp.iss')
if ($LASTEXITCODE -ne 0 -or !(Test-Path -LiteralPath $destination)) { throw 'Installer compilation failed.' }
Write-Output $destination
