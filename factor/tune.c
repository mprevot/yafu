#include "yafu_string.h"
#include "arith.h"
#include "factor.h"
#include "qs.h"
#include "gnfs.h"

void factor_tune(void)
{
	// perform trial runs on a set of inputs with known solutions using siqs and nfs
	// compute crossover points and time estimation coefficients
	// write all this info to the .ini file
	char siqslist[10][200];
	z n;
	int i;

	zInit(&n);

	//start with c60, increment by 5 digits, up to a c100
	strcpy(siqslist[0],"349594255864176572614071853194924838158088864370890996447417");
	strcpy(siqslist[1],"34053408309992030649212497354061832056920539397279047809781589871");
	strcpy(siqslist[2],"6470287906463336878241474855987746904297564226439499503918586590778209");
	strcpy(siqslist[3],"281396163585532137380297959872159569353696836686080935550459706878100362721");
	strcpy(siqslist[4],"33727095233132290409342213138708322681737322487170896778164145844669592994743377");
	strcpy(siqslist[5],"1877138824359859508015524119652506869600959721781289179190693027302028679377371001561");

	//c105: 466734409955806375058988820327650664396976790744285564594552020197119774272189758795312820988691316775181
	// for each of the siqs inputs
	for (i=0; i<10; i++)
	{
		fact_obj_t *fobj = (fact_obj_t *)malloc(sizeof(fact_obj_t));
		init_factobj(fobj);
		zCopy(&fobj->fobj_factors[i].factor,&fobj->N);

		//measure how long it takes to gather a fixed number of relations 
		str2hexz(siqslist[i],&n);
		zCopy(&n,&fobj->qs_obj.n);
		SIQS(fobj);
		clear_factor_list(fobj);

		free_factobj(fobj);
		free(fobj);
	}

	zFree(&n);
	return;
}