#ifndef VOXELS_BLOCK_H
#define VOXELS_BLOCK_H

class Block {
 public:
  static Block* blocks[256];

  const unsigned int id;
  //  0 1   2 3   4 5
  int textureFaces[6];  // -x,x, -y,y, -z,z
  unsigned char emission[3];
  unsigned char drawGroup = 0;
  bool lightPassing = false;

  Block(unsigned int id, int texture);
};

#endif