#ifndef _AJS_H_
#define _AJS_H_

GLuint getPpm();
void buildBoss(Boss *&boss);
GLuint getBossPpm();
void deleteBulletBoss(Game *&g, Bullet *&node);
void BossMvmtBulletCol(Game *&g, Boss *&boss, bool &hadBoss);





#endif
