#ifndef _SEMVER_H_
#define _SEMVER_H_

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct {
  int major;
  int minor;
  int patch;
}tSemverVersion;

int SemVer_ConvertFromStr( tSemverVersion* me, char* str );
int SemVer_ConvertToStr( tSemverVersion* me, char* str );
int SemVer_IncreaseMajor( tSemverVersion* me, int amount );
int SemVer_IncreaseMinor( tSemverVersion* me, int amount );
int SemVer_IncreasePatch( tSemverVersion* me, int amount );

#ifdef __cplusplus
}
#endif

#endif