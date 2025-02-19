xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 52;
 -2.96261;1.89970;-1.82217;,
 -0.12110;1.89970;-1.82217;,
 -0.12110;0.59904;-1.82217;,
 -2.96261;0.59904;-1.82217;,
 -0.12110;-0.70162;-1.82217;,
 -2.96261;-0.70162;-1.82217;,
 -0.12110;-2.00226;-1.82217;,
 -2.96261;-2.00225;-1.82217;,
 -0.12110;1.89970;-0.52151;,
 -0.12110;0.59904;-0.52151;,
 -0.12110;-0.70162;-0.52151;,
 -0.12110;-2.00226;-0.52151;,
 -0.12110;1.89970;0.77913;,
 -0.12110;0.59904;0.77913;,
 -0.12110;-0.70162;0.77913;,
 -0.12110;-2.00226;0.77913;,
 -0.12110;1.89970;2.07979;,
 -0.12110;0.59904;2.07979;,
 -0.12110;-0.70162;2.07979;,
 -0.12110;-2.00226;2.07979;,
 -2.96261;1.89970;2.07979;,
 -2.96261;0.59904;2.07979;,
 -2.96261;-0.70162;2.07979;,
 -2.96261;-2.00225;2.07979;,
 -2.96261;1.89970;0.77913;,
 -2.96261;1.06605;1.24614;,
 -2.96261;-1.16860;1.24614;,
 -2.96261;-2.00225;0.77913;,
 -2.96261;1.89970;-0.52151;,
 -2.96261;1.06605;-0.98851;,
 -5.87848;1.06605;1.24614;,
 -5.87848;1.06605;-0.98851;,
 -5.87848;-1.16860;-0.98851;,
 -5.87848;-1.16860;1.24614;,
 -2.96261;-1.16860;-0.98851;,
 -2.96261;-2.00225;-0.52151;,
 -2.96261;1.89970;-1.82217;,
 -2.96261;0.59904;-1.82217;,
 -2.96261;-0.70162;-1.82217;,
 -2.96261;-2.00225;-1.82217;,
 -2.96261;-2.00225;0.77913;,
 -0.12110;-2.00226;0.77913;,
 -0.12110;-2.00226;2.07979;,
 -2.96261;-2.00225;2.07979;,
 -2.96261;-2.00225;-0.52151;,
 -0.12110;-2.00226;-0.52151;,
 -2.96261;1.89970;2.07979;,
 -0.12110;1.89970;2.07979;,
 -0.12110;1.89970;0.77913;,
 -2.96261;1.89970;0.77913;,
 -0.12110;1.89970;-0.52151;,
 -2.96261;1.89970;-0.52151;;
 
 34;
 4;0,1,2,3;,
 4;3,2,4,5;,
 4;5,4,6,7;,
 4;1,8,9,2;,
 4;2,9,10,4;,
 4;4,10,11,6;,
 4;8,12,13,9;,
 4;9,13,14,10;,
 4;10,14,15,11;,
 4;12,16,17,13;,
 4;13,17,18,14;,
 4;14,18,19,15;,
 4;16,20,21,17;,
 4;17,21,22,18;,
 4;18,22,23,19;,
 4;20,24,25,21;,
 4;21,25,26,22;,
 4;22,26,27,23;,
 4;24,28,29,25;,
 4;30,31,32,33;,
 4;26,34,35,27;,
 4;28,36,37,29;,
 4;29,37,38,34;,
 4;34,38,39,35;,
 4;40,41,42,43;,
 4;44,45,41,40;,
 4;7,6,45,44;,
 4;46,47,48,49;,
 4;49,48,50,51;,
 4;51,50,1,0;,
 4;25,30,33,26;,
 4;26,33,32,34;,
 4;34,32,31,29;,
 4;29,31,30,25;;
 
 MeshMaterialList {
  4;
  34;
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1;;
  Material {
   0.400000;0.400000;0.400000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.256000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.256000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  9;
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  -0.000001;-1.000000;0.000000;,
  -0.000001;-1.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;0.000000;,
  0.000001;1.000000;0.000000;;
  34;
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;5,5,4,4;,
  4;5,5,5,5;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;2,2,2,2;,
  4;7,7,7,7;,
  4;0,0,0,0;,
  4;8,8,8,8;;
 }
 MeshTextureCoords {
  52;
  0.375000;0.000000;,
  0.375000;0.250000;,
  0.458330;0.250000;,
  0.458330;0.000000;,
  0.541670;0.250000;,
  0.541670;0.000000;,
  0.625000;0.250000;,
  0.625000;0.000000;,
  0.375000;0.333330;,
  0.458330;0.333330;,
  0.541670;0.333330;,
  0.625000;0.333330;,
  0.375000;0.416670;,
  0.458330;0.416670;,
  0.541670;0.416670;,
  0.625000;0.416670;,
  0.375000;0.500000;,
  0.458330;0.500000;,
  0.541670;0.500000;,
  0.625000;0.500000;,
  0.375000;0.750000;,
  0.458330;0.750000;,
  0.541670;0.750000;,
  0.625000;0.750000;,
  0.375000;0.833330;,
  0.458330;0.833330;,
  0.541670;0.833330;,
  0.625000;0.833330;,
  0.375000;0.916670;,
  0.458330;0.916670;,
  0.458330;0.833330;,
  0.458330;0.916670;,
  0.541670;0.916670;,
  0.541670;0.833330;,
  0.541670;0.916670;,
  0.625000;0.916670;,
  0.375000;1.000000;,
  0.458330;1.000000;,
  0.541670;1.000000;,
  0.625000;1.000000;,
  0.791670;0.000000;,
  0.791670;0.250000;,
  0.875000;0.250000;,
  0.875000;0.000000;,
  0.708330;0.000000;,
  0.708330;0.250000;,
  0.125000;0.000000;,
  0.125000;0.250000;,
  0.208330;0.250000;,
  0.208330;0.000000;,
  0.291670;0.250000;,
  0.291670;0.000000;;
 }
}
