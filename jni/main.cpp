#include <jni.h>
#include <dlfcn.h>
#include <Substrate.h>

class Block{
public:
 static Block* mAir;
 static Block* mStrippedBirchLog;
};

struct BlockVolume{
 Block** blocks;
};

// change terrain of Overworld
// OverworldGenerator::prepareHeights

void (*_OverworldGenerator$prepareHeights)(void*,BlockVolume&,int,int);
void OverworldGenerator$prepareHeights(void* self,BlockVolume& volume,int x,int z){

 // generate normal terrain
 _OverworldGenerator$prepareHeights(self,volume,x,z);
 
 // replace all blocks except air with stripped birch logs
 for(size_t x=0;x<0x10;x++){
  for(size_t z=0;z<0x10;z++){
   for(size_t y=0;y<0x80;y++){
    if(volume.blocks[x*0x10*0x80+z*0x80+y]!=Block::mAir){
     volume.blocks[x*0x10*0x80+z*0x80+y]=Block::mStrippedBirchLog;
    }
   }
  }
 }
};

JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* reserved) {
	MSHookFunction((void*)dlsym((void*)dlopen("libminecraftpe.so", RTLD_LAZY),"_ZN18OverworldGenerator14prepareHeightsER11BlockVolumeii"),(void*)&OverworldGenerator$prepareHeights,(void**)&_OverworldGenerator$prepareHeights);
	return JNI_VERSION_1_2;
}
