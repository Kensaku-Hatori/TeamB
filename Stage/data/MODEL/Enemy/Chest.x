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
 172;
 0.63734;0.03623;-0.12568;,
 -0.63734;0.03623;-0.12568;,
 -0.63734;0.63203;-0.12568;,
 0.63734;0.63203;-0.12568;,
 0.63734;4.80269;-0.12568;,
 -0.63734;4.80269;-0.12568;,
 -0.63734;4.80269;0.71739;,
 0.63734;4.80269;0.71739;,
 0.63734;0.63203;0.71739;,
 -0.63734;0.63203;0.71739;,
 -0.63734;0.03623;0.71739;,
 0.63734;0.03623;0.71739;,
 -0.63734;0.03623;-0.12568;,
 0.63734;0.03623;-0.12568;,
 -2.85557;0.03623;-0.12568;,
 -2.85557;0.03623;0.71739;,
 -2.85557;0.63203;0.71739;,
 -2.85557;0.63203;-0.12568;,
 2.85557;0.03623;0.71739;,
 2.85557;0.03623;-0.12568;,
 2.85557;0.63203;-0.12568;,
 2.85557;0.63203;0.71739;,
 0.63734;2.41946;0.71739;,
 0.63734;2.41946;-0.12568;,
 0.63734;3.61107;-0.12568;,
 0.63734;3.61107;0.71739;,
 0.63734;3.61107;0.71739;,
 -0.63734;3.61107;0.71739;,
 -0.63734;2.41946;0.71739;,
 0.63734;2.41946;0.71739;,
 -0.63734;2.41946;-0.12568;,
 -0.63734;2.41946;0.71739;,
 -0.63734;3.61107;0.71739;,
 -0.63734;3.61107;-0.12568;,
 0.63734;1.52575;-0.12568;,
 -0.63734;1.52575;-0.12568;,
 0.63734;1.52575;0.71739;,
 0.63734;0.63203;0.71739;,
 -0.63734;1.52575;0.71739;,
 0.63734;1.52575;0.71739;,
 -0.63734;1.52575;0.71739;,
 -0.63734;0.63203;0.71739;,
 -0.63734;0.03623;0.71739;,
 -1.74645;0.03623;0.71739;,
 -1.74645;0.03623;-0.12568;,
 -1.74645;0.63203;0.71739;,
 -1.74645;0.63203;-0.12568;,
 0.63734;0.03623;0.71739;,
 1.74645;0.03623;-0.12568;,
 1.74645;0.03623;0.71739;,
 1.74645;0.63203;-0.12568;,
 1.74645;0.63203;0.71739;,
 1.74645;0.03623;-2.00878;,
 1.74645;0.63203;-2.00878;,
 2.85557;0.63203;-2.00878;,
 2.85557;0.03623;-2.00878;,
 -1.67479;0.63203;-2.00878;,
 -1.67479;0.03623;-2.00878;,
 -2.85557;0.03623;-2.00878;,
 -2.85557;0.63203;-2.00878;,
 1.74645;0.63203;-1.06723;,
 1.74645;0.03623;-1.06723;,
 2.85557;0.63203;-1.06723;,
 2.85557;0.03623;-1.06723;,
 -1.67479;0.03623;-1.06723;,
 -1.67479;0.63203;-1.06723;,
 -2.85557;0.03623;-1.06723;,
 -2.85557;0.63203;-1.06723;,
 -1.67479;0.03623;-1.06723;,
 -1.67479;0.63203;-1.06723;,
 -1.67479;0.63203;-2.00878;,
 -1.67479;0.03623;-2.00878;,
 0.55910;0.63203;-1.06723;,
 0.55910;0.03623;-1.06723;,
 0.55910;0.63203;-2.00878;,
 0.55910;0.03623;-2.00878;,
 0.55910;4.72175;-1.06723;,
 0.55910;4.72175;-2.00878;,
 0.03583;4.72175;-1.06723;,
 0.03583;4.72175;-2.00878;,
 -0.62656;4.72175;-2.00878;,
 -0.62656;4.72175;-1.06723;,
 0.03583;0.03623;-1.06723;,
 0.03583;0.63203;-1.06723;,
 -0.62656;0.63203;-1.06723;,
 -0.62656;0.03623;-1.06723;,
 0.03583;0.03623;-2.00878;,
 -0.62656;0.03623;-2.00878;,
 0.03583;0.63203;-2.00878;,
 -0.62656;0.63203;-2.00878;,
 2.79017;3.61107;0.71739;,
 2.79017;3.61107;-0.12568;,
 2.79017;4.80269;-0.12568;,
 2.79017;4.80269;0.71739;,
 -2.79017;3.61107;-0.12568;,
 -2.79017;3.61107;0.71739;,
 -2.79017;4.80269;0.71739;,
 -2.79017;4.80269;-0.12568;,
 2.77460;2.41946;0.71739;,
 2.77460;1.52575;0.71739;,
 2.77460;1.52575;-0.12568;,
 2.77460;2.41946;-0.12568;,
 -2.77460;2.41946;-0.12568;,
 -2.77460;1.52575;-0.12568;,
 -2.77460;1.52575;0.71739;,
 -2.77460;2.41946;0.71739;,
 1.70597;1.52575;0.71739;,
 1.70597;2.41946;0.71739;,
 1.70597;1.52575;-0.12568;,
 1.70597;2.41946;-0.12568;,
 -1.70597;1.52575;-0.12568;,
 -1.70597;2.41946;-0.12568;,
 -1.70597;1.52575;0.71739;,
 -1.70597;2.41946;0.71739;,
 1.70597;1.52575;-2.04600;,
 1.70597;2.41946;-2.04600;,
 2.77460;2.41946;-2.04600;,
 2.77460;1.52575;-2.04600;,
 -1.70597;2.41946;-2.04600;,
 -1.70597;1.52575;-2.04600;,
 -2.77460;1.52575;-2.04600;,
 -2.77460;2.41946;-2.04600;,
 1.70597;2.41946;-1.08584;,
 1.70597;1.52575;-1.08584;,
 2.77460;2.41946;-1.08584;,
 2.77460;1.52575;-1.08584;,
 -1.70597;1.52575;-1.08584;,
 -1.70597;2.41946;-1.08584;,
 -2.77460;1.52575;-1.08584;,
 -2.77460;2.41946;-1.08584;,
 -0.97553;2.41946;-1.08584;,
 -0.97553;1.52575;-1.08584;,
 -0.97553;1.52575;-2.04600;,
 -0.97553;2.41946;-2.04600;,
 0.97553;1.52575;-1.08584;,
 0.97553;2.41946;-1.08584;,
 0.97553;2.41946;-2.04600;,
 0.97553;1.52575;-2.04600;,
 1.71375;3.61107;-0.12568;,
 1.71375;3.61107;0.71739;,
 1.71375;4.80269;-0.12568;,
 0.63734;4.80269;0.71739;,
 1.71375;4.80269;0.71739;,
 -1.71375;3.61107;0.71739;,
 -1.71375;3.61107;-0.12568;,
 -0.63734;4.80269;0.71739;,
 -1.71375;4.80269;0.71739;,
 -1.71375;4.80269;-0.12568;,
 -1.71375;4.80269;-2.28681;,
 -1.71375;3.61107;-2.28681;,
 -2.79017;3.61107;-2.28681;,
 -2.79017;4.80269;-2.28681;,
 1.71375;3.61107;-2.28681;,
 1.71375;4.80269;-2.28681;,
 2.79017;4.80269;-2.28681;,
 2.79017;3.61107;-2.28681;,
 -1.71375;3.61107;-1.20624;,
 -1.71375;4.80269;-1.20624;,
 -2.79017;3.61107;-1.20624;,
 -2.79017;4.80269;-1.20624;,
 1.71375;4.80269;-1.20624;,
 1.71375;3.61107;-1.20624;,
 2.79017;4.80269;-1.20624;,
 2.79017;3.61107;-1.20624;,
 -0.79359;4.80269;-1.20624;,
 -0.79359;3.61107;-1.20624;,
 -0.79359;3.61107;-2.28681;,
 -0.79359;4.80269;-2.28681;,
 0.79359;3.61107;-1.20624;,
 0.79359;4.80269;-1.20624;,
 0.79359;4.80269;-2.28681;,
 0.79359;3.61107;-2.28681;;
 
 170;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;11,10,12,13;,
 4;14,15,16,17;,
 4;18,19,20,21;,
 4;22,23,24,25;,
 4;26,27,28,29;,
 4;30,31,32,33;,
 4;34,3,2,35;,
 4;36,37,3,34;,
 4;38,9,8,39;,
 4;40,35,2,41;,
 4;1,42,43,44;,
 4;42,41,45,43;,
 4;41,2,46,45;,
 4;2,1,44,46;,
 4;47,0,48,49;,
 4;0,3,50,48;,
 4;3,37,51,50;,
 4;37,47,49,51;,
 4;52,53,54,55;,
 4;49,48,19,18;,
 4;51,49,18,21;,
 4;50,51,21,20;,
 4;45,46,17,16;,
 4;43,45,16,15;,
 4;44,43,15,14;,
 4;56,57,58,59;,
 4;48,50,60,61;,
 4;50,20,62,60;,
 4;20,19,63,62;,
 4;19,48,61,63;,
 4;46,44,64,65;,
 4;44,14,66,64;,
 4;14,17,67,66;,
 4;17,46,65,67;,
 4;68,69,70,71;,
 4;63,61,52,55;,
 4;62,63,55,54;,
 4;60,62,54,53;,
 4;66,67,59,58;,
 4;64,66,58,57;,
 4;65,64,57,56;,
 4;67,65,56,59;,
 4;61,60,72,73;,
 4;60,53,74,72;,
 4;53,52,75,74;,
 4;52,61,73,75;,
 3;76,77,78;,
 3;77,79,78;,
 3;79,80,78;,
 3;80,81,78;,
 3;73,72,82;,
 3;72,83,82;,
 3;83,84,82;,
 3;84,85,82;,
 3;75,73,86;,
 3;73,82,86;,
 3;82,85,86;,
 3;85,87,86;,
 3;74,75,88;,
 3;75,86,88;,
 3;86,87,88;,
 3;87,89,88;,
 4;84,89,70,69;,
 4;85,84,69,68;,
 4;87,85,68,71;,
 4;89,87,71,70;,
 4;72,74,77,76;,
 3;77,74,79;,
 3;74,88,79;,
 3;88,89,79;,
 3;89,80,79;,
 4;89,84,81,80;,
 3;72,76,83;,
 3;76,78,83;,
 3;78,81,83;,
 3;81,84,83;,
 4;24,33,5,4;,
 4;90,91,92,93;,
 4;7,6,27,26;,
 4;94,95,96,97;,
 3;23,34,24;,
 3;34,35,24;,
 3;24,35,30;,
 3;30,33,24;,
 4;98,99,100,101;,
 4;28,38,39,29;,
 4;102,103,104,105;,
 4;22,36,106,107;,
 4;36,34,108,106;,
 4;34,23,109,108;,
 4;23,22,107,109;,
 4;30,35,110,111;,
 4;35,40,112,110;,
 4;40,31,113,112;,
 4;31,30,111,113;,
 4;114,115,116,117;,
 4;106,108,100,99;,
 4;107,106,99,98;,
 4;109,107,98,101;,
 4;113,111,102,105;,
 4;112,113,105,104;,
 4;110,112,104,103;,
 4;118,119,120,121;,
 4;108,109,122,123;,
 4;109,101,124,122;,
 4;101,100,125,124;,
 4;100,108,123,125;,
 4;111,110,126,127;,
 4;110,103,128,126;,
 4;103,102,129,128;,
 4;102,111,127,129;,
 4;128,129,121,120;,
 4;126,128,120,119;,
 4;130,131,132,133;,
 4;129,127,118,121;,
 4;134,135,136,137;,
 4;125,123,114,117;,
 4;124,125,117,116;,
 4;122,124,116,115;,
 4;127,126,131,130;,
 4;126,119,132,131;,
 4;119,118,133,132;,
 4;118,127,130,133;,
 4;123,122,135,134;,
 4;122,115,136,135;,
 4;115,114,137,136;,
 4;114,123,134,137;,
 4;25,24,138,139;,
 4;24,4,140,138;,
 4;4,141,142,140;,
 4;141,25,139,142;,
 4;33,32,143,144;,
 4;32,145,146,143;,
 4;145,5,147,146;,
 4;5,33,144,147;,
 4;146,147,97,96;,
 4;143,146,96,95;,
 4;144,143,95,94;,
 4;148,149,150,151;,
 4;152,153,154,155;,
 4;139,138,91,90;,
 4;142,139,90,93;,
 4;140,142,93,92;,
 4;147,144,156,157;,
 4;144,94,158,156;,
 4;94,97,159,158;,
 4;97,147,157,159;,
 4;138,140,160,161;,
 4;140,92,162,160;,
 4;92,91,163,162;,
 4;91,138,161,163;,
 4;158,159,151,150;,
 4;156,158,150,149;,
 4;164,165,166,167;,
 4;159,157,148,151;,
 4;168,169,170,171;,
 4;163,161,152,155;,
 4;162,163,155,154;,
 4;160,162,154,153;,
 4;157,156,165,164;,
 4;156,149,166,165;,
 4;149,148,167,166;,
 4;148,157,164,167;,
 4;161,160,169,168;,
 4;160,153,170,169;,
 4;153,152,171,170;,
 4;152,161,168,171;;
 
 MeshMaterialList {
  4;
  170;
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
  10;
  0.000000;0.000000;-1.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.999279;0.000000;0.037972;,
  0.997116;0.000000;0.075889;,
  0.000000;0.000000;-1.000000;,
  0.000000;0.000000;0.000000;;
  170;
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;5,5,5,5;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;0,0,0,0;,
  4;4,4,4,4;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;5,5,5,5;,
  4;2,2,2,2;,
  4;1,1,1,1;,
  4;0,0,0,0;,
  4;5,5,5,5;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;0,0,0,0;,
  4;5,5,5,5;,
  4;2,2,2,2;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;5,5,5,5;,
  4;0,0,0,0;,
  4;3,3,3,3;,
  4;1,1,1,1;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;7,7,6,6;,
  4;5,5,5,5;,
  4;3,3,3,3;,
  4;1,1,1,1;,
  4;3,3,3,3;,
  4;5,5,5,5;,
  4;4,4,4,4;,
  4;1,1,1,1;,
  4;3,3,3,3;,
  4;5,5,5,5;,
  4;6,6,4,4;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;1,1,1,1;,
  4;0,0,0,0;,
  4;5,5,5,5;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;5,5,5,5;,
  4;0,0,0,0;,
  4;4,4,4,4;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,8,0;,
  4;3,3,3,3;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  4;0,0,0,0;,
  4;4,4,4,4;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  3;9,9,9;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  4;4,4,4,4;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;2,2,2,2;,
  4;5,5,5,5;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;0,0,0,0;,
  4;5,5,5,5;,
  4;2,2,2,2;,
  4;1,1,1,1;,
  4;0,0,0,0;,
  4;5,5,5,5;,
  4;2,2,2,2;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;5,5,5,5;,
  4;0,0,0,0;,
  4;3,3,3,3;,
  4;1,1,1,1;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;3,3,3,3;,
  4;1,1,1,1;,
  4;3,3,3,3;,
  4;5,5,5,5;,
  4;4,4,4,4;,
  4;1,1,1,1;,
  4;3,3,3,3;,
  4;5,5,5,5;,
  4;4,4,4,4;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;5,5,5,5;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;1,1,1,1;,
  4;0,0,0,0;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;5,5,5,5;,
  4;2,2,2,2;,
  4;1,1,1,1;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;5,5,5,5;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;5,5,5,5;,
  4;2,2,2,2;,
  4;1,1,1,1;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;3,3,3,3;,
  4;1,1,1,1;,
  4;3,3,3,3;,
  4;1,1,1,1;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;3,3,3,3;,
  4;5,5,5,5;,
  4;4,4,4,4;,
  4;1,1,1,1;,
  4;3,3,3,3;,
  4;5,5,5,5;,
  4;4,4,4,4;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;5,5,5,5;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;1,1,1,1;,
  4;0,0,0,0;,
  4;5,5,5,5;;
 }
 MeshTextureCoords {
  172;
  0.375000;0.000000;,
  0.625000;0.000000;,
  0.625000;0.031250;,
  0.375000;0.031250;,
  0.375000;0.250000;,
  0.625000;0.250000;,
  0.625000;0.500000;,
  0.375000;0.500000;,
  0.375000;0.718750;,
  0.625000;0.718750;,
  0.625000;0.750000;,
  0.375000;0.750000;,
  0.625000;1.000000;,
  0.375000;1.000000;,
  0.625000;0.000000;,
  0.875000;0.000000;,
  0.875000;0.031250;,
  0.625000;0.031250;,
  0.125000;0.000000;,
  0.375000;0.000000;,
  0.375000;0.031250;,
  0.125000;0.031250;,
  0.125000;0.125000;,
  0.375000;0.125000;,
  0.375000;0.187500;,
  0.125000;0.187500;,
  0.375000;0.562500;,
  0.625000;0.562500;,
  0.625000;0.625000;,
  0.375000;0.625000;,
  0.625000;0.125000;,
  0.875000;0.125000;,
  0.875000;0.187500;,
  0.625000;0.187500;,
  0.375000;0.078120;,
  0.625000;0.078120;,
  0.125000;0.078120;,
  0.125000;0.031250;,
  0.625000;0.671880;,
  0.375000;0.671880;,
  0.875000;0.078120;,
  0.875000;0.031250;,
  0.875000;0.000000;,
  0.875000;0.000000;,
  0.625000;0.000000;,
  0.875000;0.031250;,
  0.625000;0.031250;,
  0.125000;0.000000;,
  0.375000;0.000000;,
  0.125000;0.000000;,
  0.375000;0.031250;,
  0.125000;0.031250;,
  0.375000;0.000000;,
  0.375000;0.031250;,
  0.375000;0.031250;,
  0.375000;0.000000;,
  0.625000;0.031250;,
  0.625000;0.000000;,
  0.625000;0.000000;,
  0.625000;0.031250;,
  0.375000;0.031250;,
  0.375000;0.000000;,
  0.375000;0.031250;,
  0.375000;0.000000;,
  0.625000;0.000000;,
  0.625000;0.031250;,
  0.625000;0.000000;,
  0.625000;0.031250;,
  0.375000;0.000000;,
  0.375000;0.031250;,
  0.375000;0.031250;,
  0.375000;0.000000;,
  0.375000;0.031250;,
  0.375000;0.000000;,
  0.375000;0.031250;,
  0.375000;0.000000;,
  0.375000;0.031250;,
  0.375000;0.031250;,
  0.375000;0.031250;,
  0.375000;0.031250;,
  0.375000;0.031250;,
  0.375000;0.031250;,
  0.375000;0.000000;,
  0.375000;0.031250;,
  0.375000;0.031250;,
  0.375000;0.000000;,
  0.375000;0.000000;,
  0.375000;0.000000;,
  0.375000;0.031250;,
  0.375000;0.031250;,
  0.125000;0.187500;,
  0.375000;0.187500;,
  0.375000;0.250000;,
  0.125000;0.250000;,
  0.625000;0.187500;,
  0.875000;0.187500;,
  0.875000;0.250000;,
  0.625000;0.250000;,
  0.125000;0.125000;,
  0.125000;0.078120;,
  0.375000;0.078120;,
  0.375000;0.125000;,
  0.625000;0.125000;,
  0.625000;0.078120;,
  0.875000;0.078120;,
  0.875000;0.125000;,
  0.125000;0.078120;,
  0.125000;0.125000;,
  0.375000;0.078120;,
  0.375000;0.125000;,
  0.625000;0.078120;,
  0.625000;0.125000;,
  0.875000;0.078120;,
  0.875000;0.125000;,
  0.375000;0.078120;,
  0.375000;0.125000;,
  0.375000;0.125000;,
  0.375000;0.078120;,
  0.625000;0.125000;,
  0.625000;0.078120;,
  0.625000;0.078120;,
  0.625000;0.125000;,
  0.375000;0.125000;,
  0.375000;0.078120;,
  0.375000;0.125000;,
  0.375000;0.078120;,
  0.625000;0.078120;,
  0.625000;0.125000;,
  0.625000;0.078120;,
  0.625000;0.125000;,
  0.625000;0.125000;,
  0.625000;0.078120;,
  0.625000;0.078120;,
  0.625000;0.125000;,
  0.375000;0.078120;,
  0.375000;0.125000;,
  0.375000;0.125000;,
  0.375000;0.078120;,
  0.375000;0.187500;,
  0.125000;0.187500;,
  0.375000;0.250000;,
  0.125000;0.250000;,
  0.125000;0.250000;,
  0.875000;0.187500;,
  0.625000;0.187500;,
  0.875000;0.250000;,
  0.875000;0.250000;,
  0.625000;0.250000;,
  0.625000;0.250000;,
  0.625000;0.187500;,
  0.625000;0.187500;,
  0.625000;0.250000;,
  0.375000;0.187500;,
  0.375000;0.250000;,
  0.375000;0.250000;,
  0.375000;0.187500;,
  0.625000;0.187500;,
  0.625000;0.250000;,
  0.625000;0.187500;,
  0.625000;0.250000;,
  0.375000;0.250000;,
  0.375000;0.187500;,
  0.375000;0.250000;,
  0.375000;0.187500;,
  0.625000;0.250000;,
  0.625000;0.187500;,
  0.625000;0.187500;,
  0.625000;0.250000;,
  0.375000;0.187500;,
  0.375000;0.250000;,
  0.375000;0.250000;,
  0.375000;0.187500;;
 }
}