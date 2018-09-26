#include "TestMPI.h"
#include "TestTemplate.h"
#include "TestOverrideFuncs.h"
#include "TestVariadicFunction.h"
#include "TestDataType.h"

#include "TestEcho.h"
#include "TestDenseMatrixAddABC.h"
#include "TestDenseMatrixAddAB.h"


int main(int argc, char* argv[])
{
	//TestMPI(argc, argv);
	//TestTemplateFunctions();
	//TestHex2String();
	//TestTypeInfo();
	//TestVariadicTemplateFunction();
	//TestVariadicFunction();

	//TestEchoFunc_Dense(argc, argv);
	//TestFileEchoFunc_Dense(argc, argv);
	//TestEchoFunc_Perm(argc, argv);
	TestFileEchoFunc_Perm(argc, argv);
	//TestAddFuncABC(argc, argv);
	//TestAddFuncAB(argc, argv);

	getchar();

	return 0;
}