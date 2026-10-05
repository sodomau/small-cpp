; Compile through tools/package_installer.ps1 after preparing the portable folder.
#ifndef PackageDir
  #error PackageDir must name a prepared portable package.
#endif
#ifndef OutputDir
  #error OutputDir must be supplied.
#endif
#ifndef AppVersion
  #error AppVersion must match SmallCppIDE.exe.
#endif

[Setup]
AppId={{978F5346-EE06-4EC5-87FD-9C60EBC339A7}
AppName=Small C++
AppVersion={#AppVersion}
AppPublisher=Sunghyun Cho
AppPublisherURL=https://scho.postech.ac.kr/
AppSupportURL=https://github.com/sodomau/small-cpp/issues
AppUpdatesURL=https://github.com/sodomau/small-cpp/releases
DefaultDirName={localappdata}\Programs\SmallCpp
DefaultGroupName=Small C++
PrivilegesRequired=lowest
ArchitecturesAllowed=x64compatible
ArchitecturesInstallIn64BitMode=x64compatible
MinVersion=10.0
DisableProgramGroupPage=yes
OutputDir={#OutputDir}
OutputBaseFilename=SmallCpp-v{#AppVersion}-Windows-x64-Setup
SetupIconFile=..\ide\assets\smallcpp.ico
UninstallDisplayIcon={app}\SmallCppIDE.exe
VersionInfoVersion={#AppVersion}
WizardStyle=modern
Compression=lzma2
SolidCompression=yes
CloseApplications=yes
RestartApplications=no

[Tasks]
Name: "desktopicon"; Description: "Create a desktop shortcut"; GroupDescription: "Shortcuts:"; Flags: unchecked

[Files]
Source: "{#PackageDir}\*"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs

[Icons]
Name: "{group}\Small C++"; Filename: "{app}\SmallCppIDE.exe"; WorkingDir: "{app}"
Name: "{group}\Uninstall Small C++"; Filename: "{uninstallexe}"
Name: "{userdesktop}\Small C++"; Filename: "{app}\SmallCppIDE.exe"; WorkingDir: "{app}"; Tasks: desktopicon

[Run]
Filename: "{app}\SmallCppIDE.exe"; Description: "Launch Small C++"; Flags: nowait postinstall skipifsilent

; Deliberately no student-work/settings cleanup or wildcard UninstallDelete rules.
; Inno removes its installed files and shortcuts; student-created files remain.
