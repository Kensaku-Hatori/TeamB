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
 214;
 9.26721;-3.10001;-2.61466;,
 8.10432;-3.10001;-2.61466;,
 8.10432;-1.10978;-2.61466;,
 9.26721;-1.10978;-2.61466;,
 4.04996;-3.10001;-2.61466;,
 4.04996;-3.10001;-0.00000;,
 4.04996;-1.10978;-0.00000;,
 4.04996;-1.10978;-2.61466;,
 8.10432;-3.10001;2.61466;,
 9.26721;-3.10001;2.61466;,
 9.26721;-1.10978;2.61466;,
 8.10432;-1.10978;2.61466;,
 9.26721;-3.10001;-0.00000;,
 9.26721;-3.10001;-2.61466;,
 9.26721;-1.10978;-2.61466;,
 9.26721;-1.10978;-0.00000;,
 9.26721;1.50488;-2.61466;,
 8.10432;1.50488;-2.61466;,
 8.10432;1.50488;0.00000;,
 9.26721;1.50488;0.00000;,
 9.26721;-3.10001;-0.00000;,
 8.10432;-3.10001;-0.00000;,
 6.07714;-3.10001;-2.61466;,
 6.07714;-1.10978;-2.61466;,
 6.07714;-3.10001;-0.00000;,
 4.04996;-3.10001;-0.00000;,
 4.04996;-3.10001;2.61466;,
 6.07714;-3.10001;2.61466;,
 6.07714;-1.10978;2.61466;,
 4.04996;-1.10978;2.61466;,
 6.07714;2.70584;-2.61466;,
 4.04996;2.70584;-2.61466;,
 4.04996;2.70584;0.00000;,
 6.07714;2.70584;0.00000;,
 8.10432;2.70584;-2.61466;,
 8.10432;2.70584;0.00000;,
 6.07714;-3.10001;2.61466;,
 4.04996;-3.10001;2.61466;,
 8.10432;-3.10001;2.61466;,
 9.26721;-3.10001;2.61466;,
 8.10432;1.50488;2.61466;,
 9.26721;1.50488;2.61466;,
 6.07714;1.50488;0.00000;,
 6.07714;1.50488;2.61466;,
 4.04996;1.50488;0.00000;,
 4.04996;1.50488;2.61466;,
 4.04996;1.50488;0.00000;,
 4.04996;1.50488;-2.61466;,
 4.04996;1.50488;2.61466;,
 6.07714;1.50488;2.61466;,
 8.10432;1.50488;2.61466;,
 9.26721;1.50488;2.61466;,
 9.26721;1.50488;0.00000;,
 9.26721;1.50488;-2.61466;,
 6.07714;1.50488;-2.61466;,
 4.04996;-1.10978;-3.81562;,
 4.04996;1.50488;-3.81562;,
 6.07714;1.50488;-3.81562;,
 6.07714;-1.10978;-3.81562;,
 4.04996;1.50488;-3.75488;,
 4.04996;2.70584;-3.75488;,
 6.07714;2.70584;-3.75488;,
 6.07714;1.50488;-3.75488;,
 8.10432;2.70584;-3.75488;,
 8.10432;1.50488;-3.75488;,
 6.07714;2.64510;-2.61466;,
 6.07714;2.64510;-3.81562;,
 4.04996;2.64510;-3.81562;,
 4.04996;2.64510;-2.61466;,
 5.67770;-2.37066;0.72951;,
 5.67770;-2.02068;1.38761;,
 4.20721;-2.04912;1.40741;,
 4.20721;-2.40410;0.73992;,
 5.67770;-1.47557;1.90988;,
 4.20721;-1.49623;1.93713;,
 5.67770;-0.78868;2.24520;,
 4.20721;-0.79955;2.27724;,
 5.67770;-0.02727;2.36074;,
 4.20721;-0.02727;2.39443;,
 5.67770;0.73415;2.24520;,
 4.20721;0.74501;2.27724;,
 5.67770;1.42103;1.90988;,
 4.20721;1.44170;1.93713;,
 5.67770;1.96614;1.38761;,
 4.20721;1.99459;1.40741;,
 5.67770;2.31613;0.72951;,
 4.20721;2.34957;0.73992;,
 5.67770;2.43672;0.00000;,
 4.20721;2.47188;0.00000;,
 5.67770;2.31613;-0.72951;,
 4.20721;2.34957;-0.73992;,
 5.67770;1.96614;-1.38761;,
 4.20721;1.99459;-1.40741;,
 5.67770;1.42103;-1.90988;,
 4.20721;1.44170;-1.93713;,
 5.67770;0.73415;-2.24520;,
 4.20721;0.74501;-2.27723;,
 5.67770;-0.02727;-2.36074;,
 4.20721;-0.02727;-2.39443;,
 5.67770;-0.78868;-2.24520;,
 4.20721;-0.79955;-2.27723;,
 5.67770;-1.47556;-1.90988;,
 4.20721;-1.49623;-1.93713;,
 5.67770;-2.02068;-1.38761;,
 4.20721;-2.04912;-1.40741;,
 5.67770;-2.37066;-0.72951;,
 4.20721;-2.40410;-0.73992;,
 5.67770;-2.49126;-0.00000;,
 4.20721;-2.52642;-0.00000;,
 5.67770;-2.37066;0.72951;,
 4.20721;-2.40410;0.73992;,
 5.67770;-2.02068;1.38761;,
 5.67770;-2.37066;0.72951;,
 5.67770;-0.02727;-0.00000;,
 5.67770;-1.47557;1.90988;,
 5.67770;-0.78868;2.24520;,
 5.67770;-0.02727;2.36074;,
 5.67770;0.73415;2.24520;,
 5.67770;1.42103;1.90988;,
 5.67770;1.96614;1.38761;,
 5.67770;2.31613;0.72951;,
 5.67770;2.43672;0.00000;,
 5.67770;2.31613;-0.72951;,
 5.67770;1.96614;-1.38761;,
 5.67770;1.42103;-1.90988;,
 5.67770;0.73415;-2.24520;,
 5.67770;-0.02727;-2.36074;,
 5.67770;-0.78868;-2.24520;,
 5.67770;-1.47556;-1.90988;,
 5.67770;-2.02068;-1.38761;,
 5.67770;-2.37066;-0.72951;,
 5.67770;-2.49126;-0.00000;,
 0.01898;2.17146;0.00000;,
 0.01898;2.06385;-0.65097;,
 0.01898;2.06385;0.65097;,
 0.01898;1.75154;-1.23823;,
 0.01898;1.75154;1.23823;,
 0.01898;1.26511;-1.70427;,
 0.01898;1.26511;1.70427;,
 0.01898;0.65218;-2.00349;,
 0.01898;0.65218;2.00349;,
 0.01898;-0.02727;-2.10659;,
 0.01898;-0.02727;2.10659;,
 0.01898;-0.70671;-2.00349;,
 0.01898;-0.70671;2.00349;,
 0.01898;-1.31965;-1.70427;,
 0.01898;-1.31965;1.70427;,
 0.01898;-1.80608;-1.23822;,
 0.01898;-1.80608;1.23823;,
 0.01898;-2.11838;-0.65097;,
 0.01898;-2.11839;0.65097;,
 0.01898;-2.22600;-0.00000;,
 1.52040;1.90546;-1.34536;,
 1.52040;1.37694;-1.85173;,
 1.52040;2.24479;-0.70730;,
 1.52040;2.36171;0.00000;,
 1.52040;2.24479;0.70730;,
 1.52040;1.90546;1.34536;,
 1.52040;1.37694;1.85173;,
 1.52040;0.71097;2.17684;,
 1.52040;-0.02727;2.28887;,
 1.52040;-0.76550;2.17684;,
 1.52040;-1.43148;1.85174;,
 1.52040;-1.95999;1.34536;,
 1.52040;-2.29932;0.70730;,
 1.52040;-2.41624;-0.00000;,
 1.52040;-2.29932;0.70730;,
 0.01898;-2.11839;0.65097;,
 1.52040;-2.29932;-0.70730;,
 1.52040;-1.95999;-1.34536;,
 1.52040;-1.43147;-1.85173;,
 1.52040;-0.76550;-2.17684;,
 1.52040;-0.02727;-2.28887;,
 1.52040;0.71097;-2.17684;,
 2.49294;2.45481;1.24210;,
 1.24491;2.43231;0.88388;,
 1.25154;1.26939;2.33097;,
 2.90662;1.25622;2.34673;,
 1.25741;-0.02571;2.61347;,
 3.31063;-0.02219;2.69102;,
 1.25043;-1.32572;2.32353;,
 2.96585;-1.30978;2.43600;,
 1.24727;-2.48644;0.88229;,
 2.49166;-2.62226;1.04975;,
 0.00472;2.48755;0.70824;,
 0.00488;1.27338;2.32881;,
 0.00506;-0.02937;2.61356;,
 0.00525;-1.32971;2.32143;,
 0.00541;-2.47093;0.87644;,
 -0.72886;2.48544;0.85527;,
 -3.12221;1.26167;2.31313;,
 -4.62502;-0.02935;2.60651;,
 -3.09887;-1.31900;2.30584;,
 -0.71947;-2.52459;0.86378;,
 2.52358;2.21754;1.02260;,
 2.92661;1.10130;2.07882;,
 1.26432;1.10130;2.05349;,
 1.26432;2.18431;0.67615;,
 3.32411;-0.02833;2.37359;,
 1.26432;-0.02833;2.28888;,
 2.99062;-1.15796;2.17045;,
 1.26432;-1.15796;2.04590;,
 2.52358;-2.37892;0.83720;,
 1.26432;-2.23676;0.67618;,
 0.00506;1.10130;2.05349;,
 0.00506;2.23093;0.50954;,
 0.00506;-0.02833;2.28888;,
 0.00506;-1.15796;2.04590;,
 0.00506;-2.21602;0.67538;,
 -3.12596;1.10130;2.05349;,
 -0.73636;2.23093;0.65384;,
 -4.62502;-0.02833;2.28888;,
 -3.10031;-1.15796;2.04590;,
 -0.72235;-2.27079;0.66131;;
 
 188;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;16,17,18,19;,
 4;20,21,1,0;,
 4;22,4,7,23;,
 4;24,25,4,22;,
 4;26,27,28,29;,
 4;30,31,32,33;,
 4;1,22,23,2;,
 4;21,24,22,1;,
 4;27,8,11,28;,
 4;34,30,33,35;,
 4;5,26,29,6;,
 4;36,37,25,24;,
 4;38,36,24,21;,
 4;39,38,21,20;,
 4;9,12,15,10;,
 4;18,40,41,19;,
 4;42,43,40,18;,
 4;44,45,43,42;,
 4;7,6,46,47;,
 4;29,48,46,6;,
 4;28,49,48,29;,
 4;11,50,49,28;,
 4;10,51,50,11;,
 4;15,52,51,10;,
 4;14,53,52,15;,
 4;2,17,16,3;,
 4;23,54,17,2;,
 4;55,56,57,58;,
 4;42,33,32,44;,
 4;44,32,31,47;,
 4;59,60,61,62;,
 4;17,34,35,18;,
 4;18,35,33,42;,
 4;62,61,63,64;,
 4;7,55,58,23;,
 4;23,58,57,54;,
 4;65,66,67,68;,
 4;47,56,55,7;,
 4;47,59,62,54;,
 4;30,61,60,31;,
 4;31,60,59,47;,
 4;54,62,64,17;,
 4;17,64,63,34;,
 4;34,63,61,30;,
 4;54,65,68,47;,
 4;47,68,67,56;,
 4;56,67,66,57;,
 4;57,66,65,54;,
 4;69,70,71,72;,
 4;70,73,74,71;,
 4;73,75,76,74;,
 4;75,77,78,76;,
 4;77,79,80,78;,
 4;79,81,82,80;,
 4;81,83,84,82;,
 4;83,85,86,84;,
 4;85,87,88,86;,
 4;87,89,90,88;,
 4;89,91,92,90;,
 4;91,93,94,92;,
 4;93,95,96,94;,
 4;95,97,98,96;,
 4;97,99,100,98;,
 4;99,101,102,100;,
 4;101,103,104,102;,
 4;103,105,106,104;,
 4;105,107,108,106;,
 4;107,109,110,108;,
 3;111,112,113;,
 3;114,111,113;,
 3;115,114,113;,
 3;116,115,113;,
 3;117,116,113;,
 3;118,117,113;,
 3;119,118,113;,
 3;120,119,113;,
 3;121,120,113;,
 3;122,121,113;,
 3;123,122,113;,
 3;124,123,113;,
 3;125,124,113;,
 3;126,125,113;,
 3;127,126,113;,
 3;128,127,113;,
 3;129,128,113;,
 3;130,129,113;,
 3;131,130,113;,
 3;112,131,113;,
 3;132,133,134;,
 3;133,135,134;,
 3;134,135,136;,
 3;135,137,136;,
 3;136,137,138;,
 3;137,139,138;,
 3;138,139,140;,
 3;139,141,140;,
 3;140,141,142;,
 3;141,143,142;,
 3;142,143,144;,
 3;143,145,144;,
 3;144,145,146;,
 3;145,147,146;,
 3;146,147,148;,
 3;147,149,148;,
 3;148,149,150;,
 3;149,151,150;,
 4;152,153,137,135;,
 4;154,152,135,133;,
 4;155,154,133,132;,
 4;156,155,132,134;,
 4;157,156,134,136;,
 4;158,157,136,138;,
 4;159,158,138,140;,
 4;160,159,140,142;,
 4;161,160,142,144;,
 4;162,161,144,146;,
 4;163,162,146,148;,
 4;164,163,148,150;,
 4;165,166,167,151;,
 4;168,165,151,149;,
 4;169,168,149,147;,
 4;170,169,147,145;,
 4;171,170,145,143;,
 4;172,171,143,141;,
 4;173,172,141,139;,
 4;153,173,139,137;,
 4;92,94,153,152;,
 4;90,92,152,154;,
 4;88,90,154,155;,
 4;86,88,155,156;,
 4;84,86,156,157;,
 4;82,84,157,158;,
 4;80,82,158,159;,
 4;78,80,159,160;,
 4;76,78,160,161;,
 4;74,76,161,162;,
 4;71,74,162,163;,
 4;72,71,163,164;,
 4;108,110,166,165;,
 4;106,108,165,168;,
 4;104,106,168,169;,
 4;102,104,169,170;,
 4;100,102,170,171;,
 4;98,100,171,172;,
 4;96,98,172,173;,
 4;94,96,173,153;,
 4;174,175,176,177;,
 4;177,176,178,179;,
 4;179,178,180,181;,
 4;181,180,182,183;,
 4;175,184,185,176;,
 4;176,185,186,178;,
 4;178,186,187,180;,
 4;180,187,188,182;,
 4;184,189,190,185;,
 4;185,190,191,186;,
 4;186,191,192,187;,
 4;187,192,193,188;,
 4;194,195,196,197;,
 4;195,198,199,196;,
 4;198,200,201,199;,
 4;200,202,203,201;,
 4;197,196,204,205;,
 4;196,199,206,204;,
 4;199,201,207,206;,
 4;201,203,208,207;,
 4;205,204,209,210;,
 4;204,206,211,209;,
 4;206,207,212,211;,
 4;207,208,213,212;,
 4;194,197,175,174;,
 4;195,194,174,177;,
 4;198,195,177,179;,
 4;200,198,179,181;,
 4;203,202,183,182;,
 4;202,200,181,183;,
 4;197,205,184,175;,
 4;208,203,182,188;,
 4;205,210,189,184;,
 4;210,209,190,189;,
 4;209,211,191,190;,
 4;211,212,192,191;,
 4;212,213,193,192;,
 4;213,208,188,193;;
 
 MeshMaterialList {
  1;
  188;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.536000;0.536000;0.536000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  157;
  0.000000;0.000000;-1.000000;,
  0.000000;1.000000;0.000000;,
  -1.000000;-0.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -0.000000;1.000000;0.000000;,
  -0.000000;1.000000;0.000000;,
  0.000000;-1.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  -1.000000;-0.000000;0.000000;,
  -1.000000;-0.000000;0.000000;,
  -0.000000;1.000000;0.000000;,
  -0.000000;1.000000;0.000000;,
  -0.000000;1.000000;0.000000;,
  0.023802;-0.946966;0.320450;,
  0.023542;-0.797202;0.603254;,
  0.023233;-0.571952;0.819958;,
  0.022994;-0.297705;0.954381;,
  0.022904;-0.000000;0.999738;,
  0.022993;0.297705;0.954381;,
  0.023235;0.571953;0.819957;,
  0.023545;0.797201;0.603254;,
  0.023804;0.946967;0.320448;,
  0.023904;0.999714;0.000000;,
  0.023804;0.946967;-0.320448;,
  0.023545;0.797201;-0.603254;,
  0.023233;0.571951;-0.819959;,
  0.022990;0.297705;-0.954381;,
  0.022901;-0.000000;-0.999738;,
  0.022991;-0.297707;-0.954381;,
  0.023233;-0.571949;-0.819960;,
  0.023543;-0.797201;-0.603255;,
  0.023802;-0.946966;-0.320450;,
  0.023904;-0.999714;-0.000000;,
  -1.000000;-0.000000;0.000000;,
  -1.000000;-0.000000;0.000000;,
  -1.000000;-0.000000;0.000000;,
  -0.081106;0.570213;-0.817483;,
  -0.082176;0.794720;-0.601388;,
  -0.083071;0.943960;-0.319436;,
  -0.083419;0.996515;0.000000;,
  -0.083071;0.943960;0.319436;,
  -0.082176;0.794720;0.601388;,
  -0.081107;0.570215;0.817482;,
  -0.080270;0.296820;0.951554;,
  -0.079958;-0.000001;0.996798;,
  -0.080270;-0.296816;0.951555;,
  -0.081106;-0.570214;0.817483;,
  -0.082174;-0.794722;0.601385;,
  -0.083068;-0.943959;0.319438;,
  -0.083417;-0.996515;-0.000002;,
  -0.083070;-0.943959;-0.319439;,
  -0.082175;-0.794720;-0.601387;,
  -0.081106;-0.570213;-0.817483;,
  -0.080269;-0.296820;-0.951554;,
  -0.079957;-0.000001;-0.996798;,
  -0.080269;0.296820;-0.951554;,
  -0.008301;0.572085;-0.820153;,
  -0.008410;0.797394;-0.603401;,
  -0.008501;0.947201;-0.320527;,
  -0.008537;0.999964;0.000000;,
  -0.008501;0.947201;0.320527;,
  -0.008410;0.797394;0.603401;,
  -0.008301;0.572087;0.820151;,
  -0.008214;0.297774;0.954601;,
  -0.008182;-0.000000;0.999967;,
  -0.008214;-0.297773;0.954601;,
  -0.008300;-0.572086;0.820152;,
  -0.008411;-0.797395;0.603399;,
  -0.008503;-0.947200;0.320530;,
  -0.008539;-0.999964;0.000000;,
  -0.008503;-0.947200;-0.320530;,
  -0.008411;-0.797393;-0.603402;,
  -0.008301;-0.572083;-0.820154;,
  -0.008215;-0.297776;-0.954600;,
  -0.008182;-0.000000;-0.999967;,
  -0.008215;0.297775;-0.954601;,
  0.099926;-0.733564;-0.672234;,
  0.066734;-0.500565;-0.863123;,
  0.042339;-0.017383;-0.998952;,
  0.086392;0.498186;-0.862756;,
  0.107701;0.753328;-0.648766;,
  0.062128;-0.766383;-0.639372;,
  0.040075;-0.517485;-0.854753;,
  0.021180;-0.007088;-0.999750;,
  0.045112;0.515252;-0.855851;,
  0.057274;0.772164;-0.632836;,
  -0.016558;-0.794634;-0.606863;,
  -0.008831;-0.532715;-0.846248;,
  0.000000;0.003215;-0.999995;,
  -0.004574;0.530268;-0.847818;,
  -0.008603;0.787035;-0.616849;,
  -0.057195;-0.791491;-0.608499;,
  -0.030510;-0.531024;-0.846807;,
  -0.000000;0.003215;-0.999995;,
  -0.012687;0.529164;-0.848425;,
  -0.023870;0.785313;-0.618638;,
  -0.096732;0.726356;0.680478;,
  -0.060427;0.759385;0.647830;,
  -0.037899;0.516973;0.855162;,
  -0.062187;0.500202;0.863673;,
  -0.018575;0.006434;0.999807;,
  -0.036684;0.015482;0.999207;,
  -0.041890;-0.515027;0.856150;,
  -0.080439;-0.498978;0.862874;,
  -0.054527;-0.764857;0.641888;,
  -0.103248;-0.745615;0.658329;,
  0.015863;0.787773;0.615761;,
  0.007263;0.533114;0.846012;,
  -0.002065;-0.002736;0.999994;,
  0.003008;-0.530264;0.847827;,
  0.007524;-0.780078;0.625637;,
  0.055613;0.784516;0.617610;,
  0.027619;0.532462;0.846003;,
  -0.003671;-0.002855;0.999989;,
  0.009058;-0.530273;0.847779;,
  0.020688;-0.778222;0.627648;,
  0.000000;-1.000000;-0.000000;,
  0.000000;-1.000000;-0.000000;,
  -0.000000;1.000000;0.000000;,
  -0.122241;0.567803;-0.814037;,
  -0.123845;0.791274;-0.598789;,
  -0.125187;0.939781;-0.318026;,
  -0.125709;0.992067;0.000000;,
  -0.125187;0.939781;0.318026;,
  -0.123845;0.791274;0.598789;,
  -0.122241;0.567803;0.814037;,
  -0.120986;0.295589;0.947623;,
  -0.120517;-0.000001;0.992711;,
  -0.120987;-0.295584;0.947625;,
  -0.122243;-0.567801;0.814039;,
  -0.123843;-0.791276;0.598786;,
  -0.125180;-0.939781;0.318028;,
  -0.125704;-0.992068;-0.000003;,
  -0.125184;-0.939780;-0.318030;,
  -0.123844;-0.791276;-0.598787;,
  -0.122239;-0.567803;-0.814038;,
  -0.120986;-0.295588;-0.947623;,
  -0.120518;-0.000001;-0.992711;,
  -0.120987;0.295589;-0.947623;,
  0.189702;0.659760;-0.727138;,
  0.160422;0.642947;-0.748922;,
  0.958213;0.278882;-0.063654;,
  0.963792;0.247582;-0.099033;,
  0.999655;0.020679;-0.016205;,
  0.963633;-0.262644;-0.049290;,
  0.010384;-0.638378;-0.769653;,
  0.027776;-0.648670;-0.760563;,
  0.962275;-0.254736;-0.095587;,
  -0.011847;0.624145;-0.781218;,
  0.026855;-0.624291;-0.780730;,
  -0.394222;0.627107;-0.671808;,
  -0.631346;0.683342;-0.366669;,
  -0.636111;0.744818;-0.201514;,
  -0.630214;-0.747996;-0.208162;,
  -0.627178;-0.683840;-0.372842;,
  -0.291065;-0.652074;-0.700058;;
  188;
  4;0,0,0,0;,
  4;2,2,10,9;,
  4;4,4,4,4;,
  4;8,8,8,8;,
  4;1,1,1,1;,
  4;7,7,7,7;,
  4;0,0,0,0;,
  4;7,7,7,7;,
  4;4,4,4,4;,
  4;11,12,12,11;,
  4;0,0,0,0;,
  4;7,7,7,7;,
  4;4,4,4,4;,
  4;1,11,11,1;,
  4;2,2,10,10;,
  4;7,7,7,7;,
  4;7,7,7,7;,
  4;7,7,7,7;,
  4;8,8,8,8;,
  4;1,1,1,1;,
  4;6,6,1,1;,
  4;5,5,6,6;,
  4;9,10,3,3;,
  4;10,3,3,10;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;8,8,8,8;,
  4;8,8,8,8;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;4,4,4,4;,
  4;3,3,3,3;,
  4;0,0,0,0;,
  4;8,8,8,8;,
  4;4,4,4,4;,
  4;0,0,0,0;,
  4;7,7,7,7;,
  4;8,8,8,8;,
  4;13,13,13,13;,
  4;3,3,3,9;,
  4;117,117,118,118;,
  4;11,119,13,12;,
  4;3,3,3,3;,
  4;118,118,7,7;,
  4;8,8,8,8;,
  4;1,1,119,11;,
  4;4,4,4,4;,
  4;3,3,3,3;,
  4;0,0,0,0;,
  4;8,8,8,8;,
  4;14,15,68,69;,
  4;15,16,67,68;,
  4;16,17,66,67;,
  4;17,18,65,66;,
  4;18,19,64,65;,
  4;19,20,63,64;,
  4;20,21,62,63;,
  4;21,22,61,62;,
  4;22,23,60,61;,
  4;23,24,59,60;,
  4;24,25,58,59;,
  4;25,26,57,58;,
  4;26,27,76,57;,
  4;27,28,75,76;,
  4;28,29,74,75;,
  4;29,30,73,74;,
  4;30,31,72,73;,
  4;31,32,71,72;,
  4;32,33,70,71;,
  4;33,14,69,70;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;3,35,34;,
  3;35,34,34;,
  3;34,34,36;,
  3;34,3,36;,
  3;36,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  4;38,37,120,121;,
  4;39,38,121,122;,
  4;40,39,122,123;,
  4;41,40,123,124;,
  4;42,41,124,125;,
  4;43,42,125,126;,
  4;44,43,126,127;,
  4;45,44,127,128;,
  4;46,45,128,129;,
  4;47,46,129,130;,
  4;48,47,130,131;,
  4;49,48,131,132;,
  4;50,49,132,133;,
  4;51,50,133,134;,
  4;52,51,134,135;,
  4;53,52,135,136;,
  4;54,53,136,137;,
  4;55,54,137,138;,
  4;56,55,138,139;,
  4;37,56,139,120;,
  4;58,57,37,38;,
  4;59,58,38,39;,
  4;60,59,39,40;,
  4;61,60,40,41;,
  4;62,61,41,42;,
  4;63,62,42,43;,
  4;64,63,43,44;,
  4;65,64,44,45;,
  4;66,65,45,46;,
  4;67,66,46,47;,
  4;68,67,47,48;,
  4;69,68,48,49;,
  4;70,69,49,50;,
  4;71,70,50,51;,
  4;72,71,51,52;,
  4;73,72,52,53;,
  4;74,73,53,54;,
  4;75,74,54,55;,
  4;76,75,55,56;,
  4;57,76,56,37;,
  4;97,98,99,100;,
  4;100,99,101,102;,
  4;102,101,103,104;,
  4;104,103,105,106;,
  4;98,107,108,99;,
  4;99,108,109,101;,
  4;101,109,110,103;,
  4;103,110,111,105;,
  4;107,112,113,108;,
  4;108,113,114,109;,
  4;109,114,115,110;,
  4;110,115,116,111;,
  4;77,78,83,82;,
  4;78,79,84,83;,
  4;79,80,85,84;,
  4;80,81,86,85;,
  4;82,83,88,87;,
  4;83,84,89,88;,
  4;84,85,90,89;,
  4;85,86,91,90;,
  4;87,88,93,92;,
  4;88,89,94,93;,
  4;89,90,95,94;,
  4;90,91,96,95;,
  4;140,141,141,140;,
  4;142,143,143,142;,
  4;144,142,142,144;,
  4;145,144,144,145;,
  4;146,147,147,146;,
  4;148,145,145,148;,
  4;141,149,149,141;,
  4;150,146,146,150;,
  4;149,151,151,149;,
  4;151,152,152,151;,
  4;152,153,153,152;,
  4;154,155,155,154;,
  4;155,156,156,155;,
  4;156,150,150,156;;
 }
 MeshTextureCoords {
  214;
  0.375000;0.000000;,
  0.375000;0.083330;,
  0.500000;0.083330;,
  0.500000;0.000000;,
  0.375000;0.250000;,
  0.375000;0.375000;,
  0.500000;0.375000;,
  0.500000;0.250000;,
  0.375000;0.666670;,
  0.375000;0.750000;,
  0.500000;0.750000;,
  0.500000;0.666670;,
  0.375000;0.875000;,
  0.375000;1.000000;,
  0.500000;1.000000;,
  0.500000;0.875000;,
  0.625000;0.000000;,
  0.625000;0.083330;,
  0.750000;0.083330;,
  0.750000;0.000000;,
  0.250000;0.000000;,
  0.250000;0.083330;,
  0.375000;0.166670;,
  0.500000;0.166670;,
  0.250000;0.166670;,
  0.250000;0.250000;,
  0.375000;0.500000;,
  0.375000;0.583330;,
  0.500000;0.583330;,
  0.500000;0.500000;,
  0.625000;0.166670;,
  0.625000;0.250000;,
  0.750000;0.250000;,
  0.750000;0.166670;,
  0.625000;0.083330;,
  0.750000;0.083330;,
  0.125000;0.166670;,
  0.125000;0.250000;,
  0.125000;0.083330;,
  0.125000;0.000000;,
  0.875000;0.083330;,
  0.875000;0.000000;,
  0.750000;0.166670;,
  0.875000;0.166670;,
  0.750000;0.250000;,
  0.875000;0.250000;,
  0.625000;0.375000;,
  0.625000;0.250000;,
  0.625000;0.500000;,
  0.625000;0.583330;,
  0.625000;0.666670;,
  0.625000;0.750000;,
  0.625000;0.875000;,
  0.625000;1.000000;,
  0.625000;0.166670;,
  0.500000;0.250000;,
  0.625000;0.250000;,
  0.625000;0.166670;,
  0.500000;0.166670;,
  0.625000;0.250000;,
  0.625000;0.250000;,
  0.625000;0.166670;,
  0.625000;0.166670;,
  0.625000;0.083330;,
  0.625000;0.083330;,
  0.625000;0.166670;,
  0.625000;0.166670;,
  0.625000;0.250000;,
  0.625000;0.250000;,
  0.375000;0.312500;,
  0.387500;0.312500;,
  0.387500;0.406250;,
  0.375000;0.406250;,
  0.400000;0.312500;,
  0.400000;0.406250;,
  0.412500;0.312500;,
  0.412500;0.406250;,
  0.425000;0.312500;,
  0.425000;0.406250;,
  0.437500;0.312500;,
  0.437500;0.406250;,
  0.450000;0.312500;,
  0.450000;0.406250;,
  0.462500;0.312500;,
  0.462500;0.406250;,
  0.475000;0.312500;,
  0.475000;0.406250;,
  0.487500;0.312500;,
  0.487500;0.406250;,
  0.500000;0.312500;,
  0.500000;0.406250;,
  0.512500;0.312500;,
  0.512500;0.406250;,
  0.525000;0.312500;,
  0.525000;0.406250;,
  0.537500;0.312500;,
  0.537500;0.406250;,
  0.550000;0.312500;,
  0.550000;0.406250;,
  0.562500;0.312500;,
  0.562500;0.406250;,
  0.575000;0.312500;,
  0.575000;0.406250;,
  0.587500;0.312500;,
  0.587500;0.406250;,
  0.600000;0.312500;,
  0.600000;0.406250;,
  0.612500;0.312500;,
  0.612500;0.406250;,
  0.625000;0.312500;,
  0.625000;0.406250;,
  0.626410;0.064410;,
  0.648600;0.107970;,
  0.500000;0.156250;,
  0.591840;0.029840;,
  0.548280;0.007650;,
  0.500000;-0.000000;,
  0.451720;0.007650;,
  0.408160;0.029840;,
  0.373590;0.064410;,
  0.351400;0.107970;,
  0.343750;0.156250;,
  0.351400;0.204530;,
  0.373590;0.248090;,
  0.408160;0.282660;,
  0.451720;0.304850;,
  0.500000;0.312500;,
  0.548280;0.304850;,
  0.591840;0.282660;,
  0.626410;0.248090;,
  0.648600;0.204530;,
  0.656250;0.156250;,
  0.487500;0.593750;,
  0.500000;0.593750;,
  0.475000;0.593750;,
  0.512500;0.593750;,
  0.462500;0.593750;,
  0.525000;0.593750;,
  0.450000;0.593750;,
  0.537500;0.593750;,
  0.437500;0.593750;,
  0.550000;0.593750;,
  0.425000;0.593750;,
  0.562500;0.593750;,
  0.412500;0.593750;,
  0.575000;0.593750;,
  0.400000;0.593750;,
  0.587500;0.593750;,
  0.387500;0.593750;,
  0.600000;0.593750;,
  0.375000;0.593750;,
  0.612500;0.593750;,
  0.512500;0.500000;,
  0.525000;0.500000;,
  0.500000;0.500000;,
  0.487500;0.500000;,
  0.475000;0.500000;,
  0.462500;0.500000;,
  0.450000;0.500000;,
  0.437500;0.500000;,
  0.425000;0.500000;,
  0.412500;0.500000;,
  0.400000;0.500000;,
  0.387500;0.500000;,
  0.375000;0.500000;,
  0.612500;0.500000;,
  0.625000;0.500000;,
  0.625000;0.593750;,
  0.600000;0.500000;,
  0.587500;0.500000;,
  0.575000;0.500000;,
  0.562500;0.500000;,
  0.550000;0.500000;,
  0.537500;0.500000;,
  0.000000;0.000000;,
  0.000000;0.333330;,
  0.250000;0.333330;,
  0.250000;0.000000;,
  0.500000;0.333330;,
  0.500000;0.000000;,
  0.750000;0.333330;,
  0.750000;0.000000;,
  1.000000;0.333330;,
  1.000000;0.000000;,
  0.000000;0.666670;,
  0.250000;0.666670;,
  0.500000;0.666670;,
  0.750000;0.666670;,
  1.000000;0.666670;,
  0.000000;1.000000;,
  0.250000;1.000000;,
  0.500000;1.000000;,
  0.750000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.250000;0.000000;,
  0.250000;0.333330;,
  0.000000;0.333330;,
  0.500000;0.000000;,
  0.500000;0.333330;,
  0.750000;0.000000;,
  0.750000;0.333330;,
  1.000000;0.000000;,
  1.000000;0.333330;,
  0.250000;0.666670;,
  0.000000;0.666670;,
  0.500000;0.666670;,
  0.750000;0.666670;,
  1.000000;0.666670;,
  0.250000;1.000000;,
  0.000000;1.000000;,
  0.500000;1.000000;,
  0.750000;1.000000;,
  1.000000;1.000000;;
 }
}