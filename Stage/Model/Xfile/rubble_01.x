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
 240;
 -34.89600;1.63400;-5.78500;,
 -32.93600;1.63400;-5.78500;,
 -32.93600;0.65400;-5.78500;,
 -34.89600;0.65400;-5.78500;,
 -32.93600;1.63400;-5.78500;,
 -32.93600;1.63400;-0.76500;,
 -32.93600;0.65400;-0.76500;,
 -32.93600;0.65400;-5.78500;,
 -32.93600;1.63400;-0.76500;,
 -34.89600;1.63400;-0.76500;,
 -34.89600;0.65400;-0.76500;,
 -32.93600;0.65400;-0.76500;,
 -34.89600;1.63400;-0.76500;,
 -34.89600;1.63400;-5.78500;,
 -34.89600;0.65400;-5.78500;,
 -34.89600;0.65400;-0.76500;,
 -32.93600;1.63400;-5.78500;,
 -34.89600;1.63400;-5.78500;,
 -34.89600;0.65400;-5.78500;,
 -32.93600;0.65400;-5.78500;,
 -37.20100;1.63400;-5.78500;,
 -35.24100;1.63400;-5.78500;,
 -35.24100;0.65400;-5.78500;,
 -37.20100;0.65400;-5.78500;,
 -35.24100;1.63400;-5.78500;,
 -35.24100;1.63400;-0.76500;,
 -35.24100;0.65400;-0.76500;,
 -35.24100;0.65400;-5.78500;,
 -35.24100;1.63400;-0.76500;,
 -37.20100;1.63400;-0.76500;,
 -37.20100;0.65400;-0.76500;,
 -35.24100;0.65400;-0.76500;,
 -37.20100;1.63400;-0.76500;,
 -37.20100;1.63400;-5.78500;,
 -37.20100;0.65400;-5.78500;,
 -37.20100;0.65400;-0.76500;,
 -35.24100;1.63400;-5.78500;,
 -37.20100;1.63400;-5.78500;,
 -37.20100;0.65400;-5.78500;,
 -35.24100;0.65400;-5.78500;,
 -40.65400;1.63400;-5.78500;,
 -38.69400;1.63400;-5.78500;,
 -38.69400;0.65400;-5.78500;,
 -40.65400;0.65400;-5.78500;,
 -38.69400;1.63400;-5.78500;,
 -38.69400;1.63400;-0.76500;,
 -38.69400;0.65400;-0.76500;,
 -38.69400;0.65400;-5.78500;,
 -38.69400;1.63400;-0.76500;,
 -40.65400;1.63400;-0.76500;,
 -40.65400;0.65400;-0.76500;,
 -38.69400;0.65400;-0.76500;,
 -40.65400;1.63400;-0.76500;,
 -40.65400;1.63400;-5.78500;,
 -40.65400;0.65400;-5.78500;,
 -40.65400;0.65400;-0.76500;,
 -38.69400;1.63400;-5.78500;,
 -40.65400;1.63400;-5.78500;,
 -40.65400;0.65400;-5.78500;,
 -38.69400;0.65400;-5.78500;,
 -37.79818;1.67935;-8.01839;,
 -37.25380;2.53856;-6.34298;,
 -37.12104;1.65774;-5.93439;,
 -37.66542;0.79853;-7.60981;,
 -37.25380;2.53856;-6.34298;,
 -42.02810;2.53856;-4.79172;,
 -41.89534;1.65774;-4.38313;,
 -37.12104;1.65774;-5.93439;,
 -42.02810;2.53856;-4.79172;,
 -42.57248;1.67935;-6.46714;,
 -42.43973;0.79853;-6.05855;,
 -41.89534;1.65774;-4.38313;,
 -42.57248;1.67935;-6.46714;,
 -37.79818;1.67935;-8.01839;,
 -37.66542;0.79853;-7.60981;,
 -42.43973;0.79853;-6.05855;,
 -37.25380;2.53856;-6.34298;,
 -37.79818;1.67935;-8.01839;,
 -37.66542;0.79853;-7.60981;,
 -37.12104;1.65774;-5.93439;,
 -40.15297;2.64408;-1.39941;,
 -38.31834;3.26141;-1.09188;,
 -37.97784;2.51984;-1.63460;,
 -39.81249;1.90251;-1.94214;,
 -38.31834;3.26141;-1.09188;,
 -38.03874;0.38549;3.01315;,
 -37.69825;-0.35607;2.47043;,
 -37.97784;2.51984;-1.63460;,
 -38.03874;0.38549;3.01315;,
 -39.87338;-0.23184;2.70561;,
 -39.53288;-0.97340;2.16290;,
 -37.69825;-0.35607;2.47043;,
 -39.87338;-0.23184;2.70561;,
 -40.15297;2.64408;-1.39941;,
 -39.81249;1.90251;-1.94214;,
 -39.53288;-0.97340;2.16290;,
 -38.31834;3.26141;-1.09188;,
 -40.15297;2.64408;-1.39941;,
 -39.81249;1.90251;-1.94214;,
 -37.97784;2.51984;-1.63460;,
 -41.28129;3.24505;-5.98195;,
 -39.51982;3.96339;-5.50996;,
 -39.17290;3.05158;-5.41701;,
 -40.93436;2.33324;-5.88898;,
 -39.51982;3.96339;-5.50996;,
 -40.81910;3.96339;-0.66102;,
 -40.47217;3.05158;-0.56805;,
 -39.17290;3.05158;-5.41701;,
 -40.81910;3.96339;-0.66102;,
 -42.58055;3.24505;-1.13300;,
 -42.23364;2.33324;-1.04004;,
 -40.47217;3.05158;-0.56805;,
 -42.58055;3.24505;-1.13300;,
 -41.28129;3.24505;-5.98195;,
 -40.93436;2.33324;-5.88898;,
 -42.23364;2.33324;-1.04004;,
 -39.51982;3.96339;-5.50996;,
 -41.28129;3.24505;-5.98195;,
 -40.93436;2.33324;-5.88898;,
 -39.17290;3.05158;-5.41701;,
 -42.94100;1.58700;-5.78500;,
 -40.98100;1.58700;-5.78500;,
 -40.98100;0.60700;-5.78500;,
 -42.94100;0.60700;-5.78500;,
 -40.98100;1.58700;-5.78500;,
 -40.98100;1.58700;-0.76500;,
 -40.98100;0.60700;-0.76500;,
 -40.98100;0.60700;-5.78500;,
 -40.98100;1.58700;-0.76500;,
 -42.94100;1.58700;-0.76500;,
 -42.94100;0.60700;-0.76500;,
 -40.98100;0.60700;-0.76500;,
 -42.94100;1.58700;-0.76500;,
 -42.94100;1.58700;-5.78500;,
 -42.94100;0.60700;-5.78500;,
 -42.94100;0.60700;-0.76500;,
 -40.98100;1.58700;-5.78500;,
 -42.94100;1.58700;-5.78500;,
 -42.94100;0.60700;-5.78500;,
 -40.98100;0.60700;-5.78500;,
 -34.15690;2.59600;-5.82626;,
 -32.67767;2.59600;-4.54038;,
 -32.67767;1.61600;-4.54038;,
 -34.15690;1.61600;-5.82626;,
 -32.67767;2.59600;-4.54038;,
 -35.97110;2.59600;-0.75174;,
 -35.97110;1.61600;-0.75174;,
 -32.67767;1.61600;-4.54038;,
 -35.97110;2.59600;-0.75174;,
 -37.45033;2.59600;-2.03762;,
 -37.45033;1.61600;-2.03762;,
 -35.97110;1.61600;-0.75174;,
 -37.45033;2.59600;-2.03762;,
 -34.15690;2.59600;-5.82626;,
 -34.15690;1.61600;-5.82626;,
 -37.45033;1.61600;-2.03762;,
 -32.67767;2.59600;-4.54038;,
 -34.15690;2.59600;-5.82626;,
 -34.15690;1.61600;-5.82626;,
 -32.67767;1.61600;-4.54038;,
 -36.80778;1.11436;-0.25802;,
 -34.95457;1.11436;-0.89615;,
 -34.95457;0.13436;-0.89615;,
 -36.80778;0.13436;-0.25802;,
 -34.95457;1.11436;-0.89615;,
 -33.32022;1.11436;3.85036;,
 -33.32022;0.13436;3.85036;,
 -34.95457;0.13436;-0.89615;,
 -33.32022;1.11436;3.85036;,
 -35.17343;1.11436;4.48847;,
 -35.17343;0.13436;4.48847;,
 -33.32022;0.13436;3.85036;,
 -35.17343;1.11436;4.48847;,
 -36.80778;1.11436;-0.25802;,
 -36.80778;0.13436;-0.25802;,
 -35.17343;0.13436;4.48847;,
 -34.95457;1.11436;-0.89615;,
 -36.80778;1.11436;-0.25802;,
 -36.80778;0.13436;-0.25802;,
 -34.95457;0.13436;-0.89615;,
 -33.97266;2.59600;-2.83377;,
 -32.35740;2.59600;-1.72362;,
 -32.35740;1.61600;-1.72362;,
 -33.97266;1.61600;-2.83377;,
 -32.35740;2.59600;-1.72362;,
 -35.20075;2.59600;2.41349;,
 -35.20075;1.61600;2.41349;,
 -32.35740;1.61600;-1.72362;,
 -35.20075;2.59600;2.41349;,
 -36.81601;2.59600;1.30335;,
 -36.81601;1.61600;1.30335;,
 -35.20075;1.61600;2.41349;,
 -36.81601;2.59600;1.30335;,
 -33.97266;2.59600;-2.83377;,
 -33.97266;1.61600;-2.83377;,
 -36.81601;1.61600;1.30335;,
 -32.35740;2.59600;-1.72362;,
 -33.97266;2.59600;-2.83377;,
 -33.97266;1.61600;-2.83377;,
 -32.35740;1.61600;-1.72362;,
 -36.82355;2.59600;5.48625;,
 -37.07939;2.59600;7.42946;,
 -37.07939;1.61600;7.42946;,
 -36.82355;1.61600;5.48625;,
 -37.07939;2.59600;7.42946;,
 -42.05645;2.59600;6.77421;,
 -42.05645;1.61600;6.77421;,
 -37.07939;1.61600;7.42946;,
 -42.05645;2.59600;6.77421;,
 -41.80061;2.59600;4.83100;,
 -41.80061;1.61600;4.83100;,
 -42.05645;1.61600;6.77421;,
 -41.80061;2.59600;4.83100;,
 -36.82355;2.59600;5.48625;,
 -36.82355;1.61600;5.48625;,
 -41.80061;1.61600;4.83100;,
 -37.07939;2.59600;7.42946;,
 -36.82355;2.59600;5.48625;,
 -36.82355;1.61600;5.48625;,
 -37.07939;1.61600;7.42946;,
 -45.84975;2.59600;1.27084;,
 -43.93621;2.59600;0.84662;,
 -43.93621;1.61600;0.84662;,
 -45.84975;1.61600;1.27084;,
 -43.93621;2.59600;0.84662;,
 -42.84967;2.59600;5.74762;,
 -42.84967;1.61600;5.74762;,
 -43.93621;1.61600;0.84662;,
 -42.84967;2.59600;5.74762;,
 -44.76321;2.59600;6.17184;,
 -44.76321;1.61600;6.17184;,
 -42.84967;1.61600;5.74762;,
 -44.76321;2.59600;6.17184;,
 -45.84975;2.59600;1.27084;,
 -45.84975;1.61600;1.27084;,
 -44.76321;1.61600;6.17184;,
 -43.93621;2.59600;0.84662;,
 -45.84975;2.59600;1.27084;,
 -45.84975;1.61600;1.27084;,
 -43.93621;1.61600;0.84662;;
 
 72;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;12,5,16,17;,
 4;18,19,6,15;,
 4;20,21,22,23;,
 4;24,25,26,27;,
 4;28,29,30,31;,
 4;32,33,34,35;,
 4;32,25,36,37;,
 4;38,39,26,35;,
 4;40,41,42,43;,
 4;44,45,46,47;,
 4;48,49,50,51;,
 4;52,53,54,55;,
 4;52,45,56,57;,
 4;58,59,46,55;,
 4;60,61,62,63;,
 4;64,65,66,67;,
 4;68,69,70,71;,
 4;72,73,74,75;,
 4;72,65,76,77;,
 4;78,79,66,75;,
 4;80,81,82,83;,
 4;84,85,86,87;,
 4;88,89,90,91;,
 4;92,93,94,95;,
 4;92,85,96,97;,
 4;98,99,86,95;,
 4;100,101,102,103;,
 4;104,105,106,107;,
 4;108,109,110,111;,
 4;112,113,114,115;,
 4;112,105,116,117;,
 4;118,119,106,115;,
 4;120,121,122,123;,
 4;124,125,126,127;,
 4;128,129,130,131;,
 4;132,133,134,135;,
 4;132,125,136,137;,
 4;138,139,126,135;,
 4;140,141,142,143;,
 4;144,145,146,147;,
 4;148,149,150,151;,
 4;152,153,154,155;,
 4;152,145,156,157;,
 4;158,159,146,155;,
 4;160,161,162,163;,
 4;164,165,166,167;,
 4;168,169,170,171;,
 4;172,173,174,175;,
 4;172,165,176,177;,
 4;178,179,166,175;,
 4;180,181,182,183;,
 4;184,185,186,187;,
 4;188,189,190,191;,
 4;192,193,194,195;,
 4;192,185,196,197;,
 4;198,199,186,195;,
 4;200,201,202,203;,
 4;204,205,206,207;,
 4;208,209,210,211;,
 4;212,213,214,215;,
 4;212,205,216,217;,
 4;218,219,206,215;,
 4;220,221,222,223;,
 4;224,225,226,227;,
 4;228,229,230,231;,
 4;232,233,234,235;,
 4;232,225,236,237;,
 4;238,239,226,235;;
 
 MeshMaterialList {
  17;
  72;
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
   0.400000;0.400000;0.400000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.400000;0.400000;0.400000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.536000;0.536000;0.536000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.320000;0.280000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.608000;0.600000;0.600000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.536000;0.536000;0.536000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.536000;0.536000;0.536000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.536000;0.536000;0.536000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.320000;0.280000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.536000;0.536000;0.536000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.536000;0.536000;0.536000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.536000;0.536000;0.536000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.320000;0.280000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.536000;0.536000;0.536000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.320000;0.280000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  44;
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  0.951055;0.000004;-0.309021;,
  0.277741;0.438377;0.854802;,
  -0.951056;-0.000001;0.309019;,
  -0.055696;0.572892;-0.817736;,
  0.936045;0.314962;0.156902;,
  0.055696;-0.572891;0.817737;,
  0.258820;-0.000002;-0.965926;,
  0.898718;0.366491;0.240811;,
  -0.258820;0.000002;0.965925;,
  0.656059;0.000000;-0.754709;,
  0.754708;0.000000;0.656061;,
  -0.656060;0.000000;0.754709;,
  -0.325574;0.000000;-0.945517;,
  0.945519;0.000000;-0.325567;,
  0.325571;0.000000;0.945517;,
  0.566409;0.000000;-0.824124;,
  0.824127;0.000000;0.566406;,
  -0.566408;0.000000;0.824125;,
  0.991444;0.000000;0.130532;,
  -0.130528;0.000000;0.991445;,
  -0.991444;0.000000;-0.130534;,
  -0.216440;0.000000;-0.976296;,
  0.976296;0.000000;-0.216441;,
  0.216440;0.000000;0.976296;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  -0.277741;-0.438377;-0.854801;,
  -0.135463;0.898794;-0.416915;,
  0.135463;-0.898794;0.416915;,
  -0.936045;-0.314962;-0.156902;,
  -0.347448;0.756697;0.553795;,
  0.347449;-0.756697;-0.553795;,
  -0.898718;-0.366491;-0.240811;,
  -0.354015;0.930417;-0.094858;,
  0.354015;-0.930417;0.094858;,
  -0.754708;0.000000;-0.656061;,
  -0.945518;0.000000;0.325569;,
  -0.824127;0.000000;-0.566405;,
  0.130527;0.000000;-0.991445;,
  -0.976296;0.000000;0.216441;;
  72;
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;27,27,27,27;,
  4;28,28,28,28;,
  4;29,29,29,29;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;27,27,27,27;,
  4;28,28,28,28;,
  4;29,29,29,29;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;27,27,27,27;,
  4;28,28,28,28;,
  4;29,29,29,29;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;30,30,30,30;,
  4;31,31,31,31;,
  4;32,32,32,32;,
  4;6,6,6,6;,
  4;7,7,7,7;,
  4;8,8,8,8;,
  4;33,33,33,33;,
  4;34,34,34,34;,
  4;35,35,35,35;,
  4;9,9,9,9;,
  4;10,10,10,10;,
  4;11,11,11,11;,
  4;36,36,36,36;,
  4;37,37,37,37;,
  4;38,38,38,38;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;27,27,27,27;,
  4;28,28,28,28;,
  4;29,29,29,29;,
  4;12,12,12,12;,
  4;13,13,13,13;,
  4;14,14,14,14;,
  4;39,39,39,39;,
  4;28,28,28,28;,
  4;29,29,29,29;,
  4;15,15,15,15;,
  4;16,16,16,16;,
  4;17,17,17,17;,
  4;40,40,40,40;,
  4;28,28,28,28;,
  4;29,29,29,29;,
  4;18,18,18,18;,
  4;19,19,19,19;,
  4;20,20,20,20;,
  4;41,41,41,41;,
  4;28,28,28,28;,
  4;29,29,29,29;,
  4;21,21,21,21;,
  4;22,22,22,22;,
  4;23,23,23,23;,
  4;42,42,42,42;,
  4;28,28,28,28;,
  4;29,29,29,29;,
  4;24,24,24,24;,
  4;25,25,25,25;,
  4;26,26,26,26;,
  4;43,43,43,43;,
  4;28,28,28,28;,
  4;29,29,29,29;;
 }
 MeshTextureCoords {
  240;
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;;
 }
}