# Installing Small C++ on Windows

Windows distributions provide two ways to use the same IDE, compiler, debugger,
runtime, extensions, and bilingual tutorials:

- **Installer (`...-Setup.exe`)**: install for your Windows account, then open
  Small C++ from the Start menu. The default location is
  `%LOCALAPPDATA%\Programs\SmallCpp`. Administrator access is not required.
  An optional desktop shortcut is available.
- **Portable ZIP (`...-Windows-x64.zip`)**: extract the entire archive to a
  writable folder, then open `SmallCppIDE.exe`. There is no installation step.

## Programs and projects

New programs remain unsaved tabs until you choose Save. The initial save folder
is `Documents\SmallCpp\Programs`. New Project starts in
`Documents\SmallCpp\Projects`; its name becomes a subfolder there. You can choose
another location. New source/header files inside a project use the selected
project folder.

Small C++ asks Windows for the actual Documents location, including redirected
or OneDrive-backed folders. It creates the required default folder when saving
or creating a project, and recreates it if it was removed. Starting the IDE alone
does not create these folders. Recreating a folder does not restore deleted
files; saving an open document writes that document's current contents.

If the default folder cannot be created, choose another location. Existing files
use their own folder for Save As. Opening another file does not change the default
location for new programs or projects.

## Updating and uninstalling

Close Small C++ after saving your work, then run the newer installer. It uses the
existing installation location and replaces the application files.

Remove the installed version through **Windows Settings → Apps → Installed apps
→ Small C++ → Uninstall**, or **Uninstall Small C++** in the Start menu folder.
Uninstall removes installed files and shortcuts. It does not delete student
programs, projects, or IDE preferences. There is no recursive deletion of the
installation folder's untracked files.

To remove a portable copy, delete its extracted application folder after keeping
any work you saved there. Both distributions use the same Windows account's IDE
preferences.

## Building the installer

First prepare and validate the portable folder using `tools/package_release.ps1`
with the reviewed license notices and source-access document. Then use Inno Setup
6.3 or newer (including 7):

```powershell
./tools/package_installer.ps1 -PackageDir build/SmallCpp-v0.76.13-Windows-x64 -OutputDir build/release-assets-v0.76.13 -Compiler build/tools/inno7/ISCC.exe
```

The script reads the IDE version from its Windows executable, requires a complete
portable package, and writes under `build/`. Publish the Installer, portable ZIP,
corresponding third-party source ZIP, and SHA-256 checksums on the same release.
The Installer is generated from `distribution/SmallCpp.iss` with a stable AppId
so subsequent versions update the same application. It does not change file
associations or add the compiler to the system PATH.
