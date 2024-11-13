#include "csapp.h"

static const char *uidname(uid_t uid) {
  /* TODO: Something is missing here! */
  struct passwd *pwd;
  if ((pwd = getpwuid(uid)) == NULL){
    perror("getpwuid");
  }
  return pwd->pw_name;
}

static const char *gidname(gid_t gid) {
  /* TODO: Something is missing here! */
  struct group *grp;
  if ((grp = getgrgid(gid)) == NULL){
    perror("getgrgid");
  }
  return grp->gr_name;
}

static int getid(uid_t *uid_p, gid_t *gid_p, gid_t **gids_p) {
  gid_t *gids = NULL;
  // int ngid = 2;
  int groups;

  /* TODO: Something is missing here! */

  if ((*uid_p = getuid()) == -1){
    perror("getuid");
  }

  if ((*gid_p = getgid()) == -1){
    perror("getgid");
  }

  if ((groups = getgroups(0, gids)) == -1){
    perror("getgroups");
  }

  gids = Malloc(groups * sizeof(gid_t));
  if ((getgroups(groups, gids)) == -1){
    perror("getgroups");
  }

  *gids_p = gids;
  return groups;
}

int main(void) {
  uid_t uid;
  gid_t *gids, gid;
  int groups = getid(&uid, &gid, &gids);

  printf("uid=%d(%s) gid=%d(%s) ", uid, uidname(uid), gid, gidname(gid));
  printf("groups=%d(%s)", gids[0], gidname(gids[0]));
  for (int i = 1; i < groups; i++)
    printf(",%d(%s)", gids[i], gidname(gids[i]));
  putchar('\n');

  free(gids);

  return 0;
}
