let
  pkgs = import <nixpkgs> { };
in
pkgs.mkShell {
  name = "minnow-shell";

  packages = with pkgs; [
    nil
    nixfmt
    gnumake
    cmake
    ninja
    clang-tools
    clang
    git
    gdb
    tcpdump
    tshark
  ];

  shellHook = ''
    export CC=clang
    export CXX=clang++
  '';
}
