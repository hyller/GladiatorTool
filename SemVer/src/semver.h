//---------------------------------------------------------------------------//
//
// 
//
//---------------------------------------------------------------------------//
/// \file   semver.h
/// \brief
//---------------------------------------------------------------------------//
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

int SemVer_ConvertFromStr( tSemverVersion* ver, char* str );
int SemVer_ConvertToStr( tSemverVersion* ver, char* str );
int SemVer_IncreaseMajor( tSemverVersion* ver, int amount );
int SemVer_IncreaseMinor( tSemverVersion* ver, int amount );
int SemVer_IncreasePatch( tSemverVersion* ver, int amount );

#ifdef __cplusplus
}
#endif

#endif