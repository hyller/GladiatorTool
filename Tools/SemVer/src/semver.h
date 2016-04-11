#ifndef _SEMVER_H_
  #define _SEMVER_H_

#ifdef __cplusplus
    extern "C"
    {
#endif

  typedef struct
  {
    int major;
    int minor;
    int patch;
  }tSemverVersion;

  int SemVer_Init( tSemverVersion* me );
  int SemVer_ConvertFromStr( tSemverVersion* me,
                             char*           str );
  int SemVer_ConvertToStr( tSemverVersion* me,
                           char*           str, 
                           int             length );
  int SemVer_IncreaseMajor( tSemverVersion* me );
  int SemVer_IncreaseMinor( tSemverVersion* me );
  int SemVer_IncreasePatch( tSemverVersion* me );


#ifdef __cplusplus
    }
#endif
#endif