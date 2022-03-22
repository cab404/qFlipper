{ stdenv
, lib
, fetchFromGitHub
, pkg-config
, zlib
, libusb1
, libGL
, qmake
, wrapQtAppsHook
, mkDerivation

, qttools
, qtbase
, qt3d
, qtsvg
, qtserialport
, qtdeclarative
, qtquickcontrols
, qtquickcontrols2
, qtgraphicaleffects
, qtwayland
, timestamp
, commit
}:
let
  version = commit;
  udev_rules = ''
    #Flipper Zero serial port
    SUBSYSTEMS=="usb", ATTRS{idVendor}=="0483", ATTRS{idProduct}=="5740", ATTRS{manufacturer}=="Flipper Devices Inc.", TAG+="uaccess"
    #Flipper Zero DFU
    SUBSYSTEMS=="usb", ATTRS{idVendor}=="0483", ATTRS{idProduct}=="df11", ATTRS{manufacturer}=="STMicroelectronics", TAG+="uaccess"
  '';
in
mkDerivation {
  name = "qFlipper";
  inherit version;

  src = ../..;

  nativeBuildInputs = [
    pkg-config
    qmake
    qttools
  ];

  buildInputs = [
    zlib
    libusb1
    libGL
    wrapQtAppsHook

    qtbase
    qt3d
    qtsvg
    qtserialport
    qtdeclarative
    qtquickcontrols
    qtquickcontrols2
    qtgraphicaleffects
  ] ++ lib.optionals (stdenv.isLinux) [
    qtwayland
  ];

  qmakeFlags = [
    "DEFINES+=DISABLE_APPLICATION_UPDATES"
    "CONFIG+=qtquickcompiler"
  ];

  preBuild = ''
    substituteInPlace qflipper_common.pri \
        --replace 'GIT_VERSION = unknown' 'GIT_VERSION = "${toString version}"' \
        --replace 'GIT_TIMESTAMP = 0' 'GIT_TIMESTAMP = ${toString timestamp}' \
        --replace 'GIT_COMMIT = unknown' 'GIT_COMMIT = "${toString commit}"'
  '';

  installPhase = ''
    make install

    mkdir -p $out/bin
    ${lib.optionalString stdenv.isDarwin ''
    cp qFlipper.app/Contents/MacOS/qFlipper $out/bin
    ''}
    cp qFlipper-cli $out/bin

    mkdir -p $out/etc/udev/rules.d
    tee $out/etc/udev/rules.d/42-flipperzero.rules << EOF
    ${udev_rules}
    EOF

  '';

  meta = with lib; {
    description = "Cross-platform desktop tool to manage your flipper device";
    homepage = "https://flipperzero.one/";
    license = licenses.gpl3;
    maintainers = with maintainers; [ cab404 ];
    platforms = [ "x86_64-linux" "x86_64-darwin" "aarch64-linux" ]; # qtbase doesn't build yet on aarch64-darwin
  };

}
