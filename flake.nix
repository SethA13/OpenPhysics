{
  description = "IMGUI GLFW development";

  outputs = {nixpkgs, ...}: let
    system = "x86_64-linux";
    pkgs = nixpkgs.legacyPackages.${system};
  in {
    devShells.${system}.default = pkgs.mkShell {
      packages = with pkgs; [
        gcc
        cmake
        imgui
        freeglut
        libGLU
        libGL
        glew
        glfw
        pkg-config
        xorg.libX11
        xorg.libXau
        xorg.libXdmcp
      ];
    };
  };
}
