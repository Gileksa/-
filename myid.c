#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <pwd.h>
#include <grp.h>


int main(int ac, char *av[])
{
	int i, c, uid, gid;
	char *name_uid;
	char *name_gid;
	gid_t list[100];
	char *s2;
	int a = 0;

	if(ac == 1)
	{
		uid = getuid();
		name_uid = getpwuid(uid)->pw_name;
		
		gid = getgid();
		//*s2 = getgrgid(gid)->gr_gid;
		
		c = getgroups(100, list);
	}

	else
	{
		name_uid = av[1];
		uid = getpwnam(av[1])->pw_uid;

		gid = getpwnam(av[1])->pw_gid;
		//*s2 = getgrgid(gid)->gr_gid;
		//gid_t *s3;

		getgrouplist(name_uid, getpwuid(uid)->pw_gid, list, &c); //nado razobratsa s listom
		a++;

	}

	s2 = getgrgid(gid)->gr_name;

	printf("uid=%d(%s) gid=%d(%s) groups=%d(%s),", uid, name_uid, gid, s2, gid, s2);

	for(i = a; i < a + c - 1; i++)
	{
		printf("%d(%s)", list[i], getgrgid(list[i])->gr_name);
		printf("%s", (i != a +  c - 2) ? "," : "\n");
	}

	return 0;
}
