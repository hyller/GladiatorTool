#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stddef.h>
#include <ctype.h>
#include <unistd.h>

#include "utils.h"
#include "version.h"

#define __USE_GNU

int BUF_SIZE = 128;

//set to 1 to increment major version when minor reached 100. i.e.:
//1.99.0 + 0.01.0 = 1.100.0 = 2.0.0
#define ON_MINOR_100_INCREMENT_MAJOR_FIELD 0

typedef int version_numbers_t[3];

typedef struct version_numbers_s {
  int major;
  int minor;
  int patch;
} version_numbers;

typedef struct application_settings_s {
  int verbose;
  int quiet;
  int length;
  int output_cdef;
} application_settings;

typedef version_numbers* version_numbers_ptr;

#define VERNUMIDX2(vn,idx) (idx >= 2 ? vn.patch : vn.minor)
#define VERNUMIDX(vn,idx) (idx == 0 ? vn.major : VERNUMIDX2(vn,idx))

int increaseVersion(version_numbers* versionData, int index, int amount) {
  switch (index) {
    case 0:
      versionData->major = versionData->major + amount;
      versionData->minor = 0;
      versionData->patch = 0;
      return 1;
    case 1:
      versionData->minor = versionData->minor + amount;
      versionData->patch = 0;
  #ifdef ON_MINOR_100_INCREMENT_MAJOR_FIELD
      if (versionData->minor >= 100) {
        versionData->minor = 0;
        versionData->major = versionData->major + 1;
        return 1;
      }
  #endif
      return 1;
    case 2:
      versionData->patch = versionData->patch + amount;
      return 1;
  }
}

void echo(char * s) {
  printf("%s\n", s);
}

void usage(int argc, char** argv) {
  printf("Usage: %s v%s [version(x.y.z)] [index-to-increment] [increment-by]\n",
      argv[0], VERSION);
  printf(
      "If '-' is passed as the version number, the version will be read from stdin.\n");
  exit (EXIT_FAILURE);
}

int assign_vd_from_version_numbers(version_numbers * vd, version_numbers_t vn) {
  memcpy((version_numbers_t*) vd, vn, sizeof(int) * 3);
  return (EXIT_SUCCESS);
}

int process_flags(int argc, char **argv, application_settings* as){
  int aflag = 0;
  int bflag = 0;
  char *cvalue = NULL;
  int index;
  int c;

  opterr = 0;
  while ((c = getopt (argc, argv, "dvql:")) != -1)
    switch (c) {
      case 'd':
        as->output_cdef = 1;
        break;
      case 'v':
        as->verbose = 1;
        break;
      case 'q':
        as->quiet = 1;
        break;
      case 'l':
        as->length = atoi(optarg);
        break;
      case 'h':
        if (optopt == 'c')
          fprintf (stderr, "Option -%c requires an argument.\n", optopt);
        else if (isprint (optopt))
          fprintf (stderr, "Unknown option `-%c'.\n", optopt);
        else
          fprintf (stderr,
                   "Unknown option character `\\x%x'.\n",
                   optopt);
        return 1;
      default:
        break;
      }
  printf ("aflag = %d, bflag = %d, cvalue = %s\n",
          aflag, bflag, cvalue);

  for (index = optind; index < argc; index++)
    printf ("Non-option argument %s\n", argv[index]);
  return 0;
}

void output_new_version(application_settings* as, version_numbers* vd, int useVersionFromFile, char* filenameStr) {
  char vbuf[BUF_SIZE];
  char fmtstr[BUF_SIZE];
  if (as->output_cdef == 1) {
    sprintf((char*)fmtstr,  "#define VERSION = %s", "%d.%d.%d\n");
  } else {
    sprintf((char*)fmtstr,  "%s", "%d.%d.%d\n");
  }
  sprintf((char*) vbuf, (char*)fmtstr, (int) vd->major, (int) vd->minor, (int) vd->patch);
  printf("%s", (char*) vbuf);

  if (useVersionFromFile == 1) {
    file_write((char*) filenameStr, (char*) vbuf);
  }
}


int main(int argc, char ** argv) {
  version_numbers vd;
  char filenameStr[BUF_SIZE];
  char versionBuf[BUF_SIZE];

  application_settings as;
  zero_fill(&as, sizeof(application_settings));

  if (argc == 1) {
    usage(argc, argv);
  }

  process_flags(argc, argv, &as);

  char * versionStr = argv[1];
  //versionStr = malloc(BUF_SIZE);
  //memcpy(versionStr, argv[1], BUF_SIZE);
  int indexToIncrement = -1;
  int incrementBy;
  int useVersionFromFile = 0;

  if (file_exists(versionStr)) {
    memcpy((char*) filenameStr, versionStr, BUF_SIZE);
    file_read(versionStr, (char *) versionBuf, BUF_SIZE);
    useVersionFromFile = 1;
    memmove(versionBuf, (char*) versionBuf, BUF_SIZE);
    //printf("%s\n", versionBuf);
    memmove(versionStr, versionBuf, BUF_SIZE);
  } else {

    if (strcmp(versionStr, "-") == 0) {
      char buf[BUF_SIZE];
      int cRead = read_from_stdin((char *) buf);
      memmove(versionStr, (char*) buf, BUF_SIZE);
    }
  }

  /*
  if (strcmp(argv[2], "major")==0)
    indexToIncrement = 0;
  if (strcmp(argv[2], "minor")==0)
    indexToIncrement = 1;
  if (strcmp(argv[2], "patch")==0)
    indexToIncrement = 2;
*/

  switch (argc) {
  case 2:
    //if (indexToIncrement == -1)
      indexToIncrement = 2;
    incrementBy = 1;
    break;
  case 3:
   /// if (indexToIncrement == -1)
      indexToIncrement = 2;
    incrementBy = atoi(argv[3]);
    break;
  case 4:
   // if (indexToIncrement == -1)
      indexToIncrement = atoi(argv[2]);
    incrementBy = atoi(argv[3]);
    break;
  default:
    //indexToIncrement = 2;
    //incrementBy = 1;
    break;
  }

  if (useVersionFromFile == 1) {
    //  memmove((char*)versionStr, (char*)useVersionFromFile, BUF_SIZE);
  }

  /*
   if (strcmp(argv[2], "major") == 0)
   indexToIncrement = 0;
   if (strcmp(argv[2], "minor") == 0)
   indexToIncrement = 1;
   if (strcmp(argv[2], "patch") == 0)
   indexToIncrement = 2;  
   */
  const char s[2] = ".";
  char *token;
  char *str1 = versionStr;

  int versionNumbers[3] = { 0, 0, 0 };

  /* walk through other tokens */
  int index = 0;

  /* get the first token */
  token = strtok(str1, s);
  while (token != NULL) {
    versionNumbers[index] = atoi(token);
    token = strtok(NULL, s);
    index++;
  }

  assign_vd_from_version_numbers(&vd, versionNumbers);
  increaseVersion(&vd, indexToIncrement, incrementBy);

  output_new_version(&as, &vd, useVersionFromFile, filenameStr);

  //file_write((char*)filenameStr, (char*)vbuf);

  /**/

  return (EXIT_SUCCESS);
}
