#include "pickle.h"
#include "phpzope.h"


//  Basic PHPZOPE Class
PHPZope::PHPZope() {
}

PHPZope::~PHPZope() {
}

int PHPZope::returnValue() {
	return 8;
}
stack<StackItem>& PHPZope::retrieveCurrentStack()
{
	return this->currentStack;
}
vector<StackItem>& PHPZope::retrieveCurrentMemo()
{
	return this->theMemo;
}
int PHPZope::retrieveStackDepth() {
	stack<StackItem> theStack = this->currentStack;
	int stackDepth = theStack.size();
	return stackDepth;
}
int PHPZope::setPickle(char *pickle)
{
	this->theString.assign(pickle,strlen(pickle));
	return 0;
}
int PHPZope::readPickle(char *src)
{
	// http://en.cppreference.com/w/cpp/string/byte/strcpy
	//this->filename = new char(std::strlen(src)+10);
    	strcpy(this->filename, src);
	return 0;
} 
int PHPZope::getMemoSize()
{
	return memoSize;
}

int PHPZope::retrieve_state(ifstream& infile,string& state2,stack<StackItem>& theStack,int& lastMark,vector<StackItem>& theMemo)
        {
	std::string::iterator it;
	std::string theString;
	std::string filename = "state.txt";
	StackItem *ptrStackItem,*testStackItem;
	int result = 0;
	char opcode;
	char *ptr;
	char *buf;
	char buffer[1000];
	int saveString = -1;

	/* fetch the data : retrieve all the rows in the result set */

	this->currentStack = theStack;
	Pickle *myPickler = new Pickle();
	int num = 0;
	std::stringstream parse(state2);
	int len = parse.gcount();
	char someChar;
	int someInt;
	parse >> someChar;
	theString = parse.str();
	it = theString.begin();
	Opcode *nextOpcode;
	buf = (char*)malloc(sizeof(char)*200);
	strcpy(buf,"BEGIN");
	do
	{
	    for (int i = 0; i < OPCODE_COUNT; i++)
	    {
	    	Opcode *currentOpcode = myPickler->opcodes[i];

		if (result == 2)
		{
	    		for (int i = 0; i < OPCODE_COUNT; i++)
	    		{
	    			nextOpcode = myPickler->opcodes[i];
	        		if (nextOpcode->opcode == someChar)
				{
					break;
				}
			}
	            ptrStackItem = (StackItem*)malloc(sizeof(StackItem));
		    ptrStackItem->initialize();
		    ptrStackItem->opcode = someChar;
		    ptrStackItem->theMark = 0;
		    ptrStackItem->lastMark = lastMark;
	    	    theStack.push(*ptrStackItem);
	            result = (nextOpcode->opfunc)(infile,theString,it,*ptrStackItem,theStack,theMemo);
		    result = 1;
		}
		else if (result == 3)
		{
			someChar = '~';
	                ptrStackItem = (StackItem*)malloc(sizeof(StackItem));
		    	ptrStackItem->initialize();
		        ptrStackItem->opcode = someChar;
		        ptrStackItem->theMark = 0;
		        ptrStackItem->lastMark = lastMark;
		        ptrStackItem->someString=(char*)malloc(sizeof(char)*100);
			strcpy(ptrStackItem->someString,buf);
	    	        theStack.push(*ptrStackItem);
	            	result = (Opcode::fnGLOBAL1)(infile,theString,it,*ptrStackItem,theStack,theMemo);
	            	//result = (currentOpcode->opfunc)(infile,theString,it,*ptrStackItem,theStack,theMemo);
			getline(infile,theString);
			it = theString.begin();
			someChar = *it++;
			result = 1;
		}
		else if (result == 4)
		{
			someChar = 'U';
	                ptrStackItem = (StackItem*)malloc(sizeof(StackItem));
		    	ptrStackItem->initialize();
		        ptrStackItem->opcode = someChar;
		        ptrStackItem->theMark = 0;
		        ptrStackItem->lastMark = lastMark;
	    	        theStack.push(*ptrStackItem);
	            	result = (Opcode::fnSHORT_BINSTRING1)(infile,theString,it,*ptrStackItem,theStack,theMemo);
			result = 1;
		}	
		else if (result == 5)
		{
			result = 1;
		}
	        else if (currentOpcode->opcode == someChar)
                {
		    char *someString;
	            ptrStackItem = (StackItem*)malloc(1+sizeof(StackItem));
		    ptrStackItem->initialize();
		    ptrStackItem->opcode = someChar;
		    ptrStackItem->theMark = 0;
		    ptrStackItem->lastMark = lastMark;
		    
		    if (saveString==0)
		    {
			ptrStackItem->someString=(char*)malloc(sizeof(char)*1000);
			strcpy(ptrStackItem->someString,buf);
			ptrStackItem->hasString = 0;
			free(buf);
		    }
	    	    theStack.push(*ptrStackItem);
	            result = (currentOpcode->opfunc)(infile,theString,it,*ptrStackItem,theStack,theMemo);

		    if (ptrStackItem->hasString == 0)
		    {
			buf=(char*)malloc(sizeof(char)*strlen(ptrStackItem->someString));
			strcpy(buf,ptrStackItem->someString);
			saveString = 0;
		    }

		    if (result == 2)
		    {
		        someChar = *it++;
		    }
		    else if (result == 3)
		    {
		        getline(infile,theString);
			// If this is a newobj opcode, discard the next line
			testStackItem = &theStack.top();
			if (testStackItem->opcode == '*')
			{
		        	getline(infile,theString);
			    	it = theString.begin();
				someChar = *it;
			        result = 1;
			}
			else
			{
			    someChar = '~';
			    it = theString.begin();
			}
		    }
		    else if (result == 4)
		    {
		        getline(infile,theString);
			someChar = 'U';
			it = theString.begin();
		    }
		    else if (result == 5)
		    {
				getline(infile,theString);
				it = theString.begin();
				someChar = *it++;
			    }	
			    else
			    {
				someChar = *it;
				continueSHORT_BINSTRING = 0;
			    }

			    strcpy(buf,"BEGIN");
			    // strcpy(buf,ptrStackItem->someString);
			    ptrStackItem = &theStack.top();
			    lastMark = ptrStackItem->lastMark;	
			}
		    }
	} while ( *it != '\000' && it != theString.end() && (result == 0 || result == 2 || result == 3 || result == 4 || result == 5));

	printf("\n");
	return 0;
} // retrieve_state()

char* PHPZope::returnPickleFile(stack<StackItem>& theStack,vector<StackItem>& theMemo)
{
	memoSize = 15;
	std::string state;
	int j;
	int boolSTOP;
	int lastMark = 0;
	continueSHORT_BINSTRING = 0;

	ifstream infile;

        //__asm__("int3");
	infile.open(this->filename);
	boolSTOP = -1;
        if ( infile.fail() )
        {
	   strcpy(this->filename,strerror(errno));
	}
	else
	{
	    while (!infile.eof())
            {
		theMemo.resize(memoSize);
		getline(infile,state);
//		std::stringstream parse(state);
//	        this->retrieve_state(infile,parse,theStack,lastMark,theMemo);
	        this->retrieve_state(infile,state,theStack,lastMark,theMemo);
		memoSize += 1;
	    }
	    infile.close();
	    int i;
        }
	return this->filename;
}

char* PHPZope::returnPickleString(stack<StackItem>& theStack,vector<StackItem>& theMemo)
{
	memoSize = 15;
	int j;
	int boolSTOP;
	int lastMark = 0;
	continueSHORT_BINSTRING = 0;
	ifstream infile;
	std::string state;

	theMemo.resize(memoSize);
	std::stringstream parse(this->theString);
	this->retrieve_state(infile,state,theStack,lastMark,theMemo);
	memoSize += 1;

	return 0;
}

void phpzope_free_storage(void *object TSRMLS_DC)
{
    phpzope_object *obj = (phpzope_object *)object;
    //delete &(obj->phpzope); 

    zend_hash_destroy(obj->std.properties);
    FREE_HASHTABLE(obj->std.properties);

    free(obj);
}

zend_object_value phpzope_create_handler(zend_class_entry *type TSRMLS_DC)
{
    zval *tmp;
    zend_object_value retval;

    phpzope_object *obj = (phpzope_object *)malloc(sizeof(phpzope_object));
    memset(obj, 0, sizeof(phpzope_object));
    obj->std.ce = type;

    ALLOC_HASHTABLE(obj->std.properties);
    zend_hash_init(obj->std.properties, 0, NULL, ZVAL_PTR_DTOR, 0);
/*
    zend_hash_copy(obj->std.properties, &type->default_properties,
        (copy_ctor_func_t)zval_add_ref, (void *)&tmp, sizeof(zval *));
*/

    retval.handle = zend_objects_store_put(obj, NULL, phpzope_free_storage, NULL TSRMLS_CC);
    retval.handlers = &phpzope_object_handlers;

    return retval;
}


PHP_METHOD(PHPZope, __construct)
{
    const char *filename="test.txt";
    PHPZope *phpzope = NULL;
    zval *object = getThis();

    phpzope = new PHPZope();
    phpzope_object *obj = (phpzope_object *)zend_object_store_get_object(object TSRMLS_CC);
    obj->phpzope = phpzope;

}
PHP_METHOD(PHPZope, returnValue)
{
    PHPZope *phpzope;
    phpzope_object *obj = (phpzope_object *)zend_object_store_get_object(
        getThis() TSRMLS_CC);
    phpzope = obj->phpzope;
    if (phpzope != NULL) {
        RETURN_LONG(phpzope->returnValue());
    }
    RETURN_NULL();
}
PHP_METHOD(PHPZope, setPickle)
{
    PHPZope *phpzope;
    char *ptr,*ptr2;
    char name[1000];
    int name_len;
    phpzope_object *obj = (phpzope_object *)zend_object_store_get_object(
        getThis() TSRMLS_CC);
    phpzope = obj->phpzope;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &ptr, &name_len) == FAILURE) {
        RETURN_NULL();
    }
    ptr2 = name;
    for (int i=0;i<name_len;i++)
    {
	*ptr2++ = *ptr++;
    }
    *ptr2 = '\0';
    ptr2 = name;
    if (phpzope != NULL) {
        phpzope->setPickle(ptr2);
    }
    RETURN_NULL();
}
PHP_METHOD(PHPZope, readPickle)
{
    PHPZope *phpzope;
    char *ptr,*ptr2;
    char name[100];
    int name_len;
    phpzope_object *obj = (phpzope_object *)zend_object_store_get_object(
        getThis() TSRMLS_CC);
    phpzope = obj->phpzope;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &ptr, &name_len) == FAILURE) {
        RETURN_NULL();
    }
    ptr2 = name;
    for (int i=0;i<name_len;i++)
    {
	*ptr2++ = *ptr++;
    }
    *ptr2 = '\0';
    ptr2 = name;
    if (phpzope != NULL) {
        phpzope->readPickle(ptr2);
    }
    RETURN_NULL();
}
PHP_METHOD(PHPZope, setPicklePath)
{
    PHPZope *phpzope;
    char *ptr,*ptr2;
    char name[100];
    int name_len;
    phpzope_object *obj = (phpzope_object *)zend_object_store_get_object(
        getThis() TSRMLS_CC);
    phpzope = obj->phpzope;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &ptr, &name_len) == FAILURE) {
        RETURN_NULL();
    }
    ptr2 = name;
    for (int i=0;i<name_len;i++)
    {
	*ptr2++ = *ptr++;
    }
    *ptr2 = '\0';
    ptr2 = name;
    if (phpzope != NULL) {
        phpzope->readPickle(ptr2);
    }
    RETURN_NULL();
}
PHP_METHOD(PHPZope, returnPickleFile)
{
    char *mystr;
    zval *mysubarray,*opcodesubarray;
    StackItem *ptrStackItem;

    array_init(return_value);
    /*
    add_index_long(return_value, 42, 123);
    add_next_index_string(return_value,"I should now be found at index 43", 1);
    add_next_index_string(return_value,"I'm at 44!", 1);
    mystr = estrdup("Forty Five");
    add_next_index_string(return_value,"pi",3.1415926535);
    */
    PHPZope *phpzope;
    phpzope_object *obj = (phpzope_object *)zend_object_store_get_object(
        getThis() TSRMLS_CC);
    phpzope = obj->phpzope;
    int count = 0;
    if (phpzope != NULL) {
	//ptrStackItem = (StackItem*)malloc(sizeof(StackItem));
	//ptrStackItem->opcode = '!';
	stack<StackItem> theStack = phpzope->retrieveCurrentStack();
	vector<StackItem> theMemo = phpzope->retrieveCurrentMemo();
	phpzope->returnPickleFile(theStack,theMemo);
	char somestring[100];
	int depth = theStack.size();
	sprintf(somestring,"stackDepth %i",depth);
	ALLOC_INIT_ZVAL(mysubarray);
	array_init(mysubarray);
	//add_next_index_string(mysubarray,somestring,1);
	//add_next_index_string(return_value,somestring,1);
	
	int stackDepth = depth;
	Pickle *myPickler = new Pickle();
	int count = 1;
	while (stackDepth > 0 )
	{
	     int result;
	     StackItem stackItem = theStack.top();
	     sprintf(somestring,"%c",stackItem.opcode);
	     for (int i = 0; i < OPCODE_COUNT; i++)
	     {
	    	Opcode *currentOpcode = myPickler->opcodes[i];
	        if (currentOpcode->opcode == stackItem.opcode)
                {
		    //depth = theStack.size();
		    ALLOC_INIT_ZVAL(opcodesubarray);
		    array_init(opcodesubarray);
		    add_assoc_string(opcodesubarray,"opcode",somestring,1);
		    add_assoc_long(opcodesubarray,"depth",depth);
	            result = (currentOpcode->opr)(opcodesubarray,&stackItem,depth);
		    sprintf(somestring,"%i",count++);
		    //add_assoc_zval(mysubarray,somestring,opcodesubarray); 
		    add_assoc_zval(return_value,somestring,opcodesubarray); 
		}
	    }
	    stackDepth--;
	    theStack.pop();
	} while (stackDepth > 1 );
	add_assoc_zval(return_value,"result",mysubarray); 

	// Now print the memo
	ALLOC_INIT_ZVAL(mysubarray);
	array_init(mysubarray);
	int memoSize;
	memoSize = phpzope->getMemoSize();
	for (int k=0; k<memoSize; k++ )
	{
	     int result;
	     StackItem memoItem = theMemo[k];
	     for (int i = 0; i < OPCODE_COUNT; i++)
	     {
	    	Opcode *currentOpcode = myPickler->opcodes[i];
	        if (currentOpcode->opcode == memoItem.opcode)
                {
		    depth = theMemo.size();
		    ALLOC_INIT_ZVAL(opcodesubarray);
		    array_init(opcodesubarray);
	            result = (currentOpcode->opr)(opcodesubarray,&memoItem,depth);
		    sprintf(somestring,"%i",k);
		    add_assoc_zval(mysubarray,somestring,opcodesubarray); 
		}
	    }
	}

	// Now print the memo


	add_assoc_zval(return_value,"theMemo",mysubarray);
    }
} 
PHP_METHOD(PHPZope, returnPickleString)
{
    char *mystr;
    zval *mysubarray,*opcodesubarray;
    StackItem *ptrStackItem;

    array_init(return_value);
    /*
    add_index_long(return_value, 42, 123);
    add_next_index_string(return_value,"I should now be found at index 43", 1);
    add_next_index_string(return_value,"I'm at 44!", 1);
    mystr = estrdup("Forty Five");
    add_next_index_string(return_value,"pi",3.1415926535);
    */
    PHPZope *phpzope;
    phpzope_object *obj = (phpzope_object *)zend_object_store_get_object(
        getThis() TSRMLS_CC);
    phpzope = obj->phpzope;
    int count = 0;
    if (phpzope != NULL) {
	//ptrStackItem = (StackItem*)malloc(sizeof(StackItem));
	//ptrStackItem->opcode = '!';
	stack<StackItem> theStack = phpzope->retrieveCurrentStack();
	vector<StackItem> theMemo = phpzope->retrieveCurrentMemo();
	phpzope->returnPickleString(theStack,theMemo);
	char somestring[100];
	int depth = theStack.size();
	sprintf(somestring,"stackDepth %i",depth);
	ALLOC_INIT_ZVAL(mysubarray);
	array_init(mysubarray);
	//add_next_index_string(mysubarray,somestring,1);
	//add_next_index_string(return_value,somestring,1);
	
	int stackDepth = depth;
	Pickle *myPickler = new Pickle();
	int count = 1;
	while (stackDepth > 0 )
	{
	     int result;
	     StackItem stackItem = theStack.top();
	     sprintf(somestring,"%c",stackItem.opcode);
	     for (int i = 0; i < OPCODE_COUNT; i++)
	     {
	    	Opcode *currentOpcode = myPickler->opcodes[i];
	        if (currentOpcode->opcode == stackItem.opcode)
                {
		    //depth = theStack.size();
		    ALLOC_INIT_ZVAL(opcodesubarray);
		    array_init(opcodesubarray);
		    add_assoc_string(opcodesubarray,"opcode",somestring,1);
		    add_assoc_long(opcodesubarray,"depth",depth);
	            result = (currentOpcode->opr)(opcodesubarray,&stackItem,depth);
		    sprintf(somestring,"%i",count++);
		    //add_assoc_zval(mysubarray,somestring,opcodesubarray); 
		    add_assoc_zval(return_value,somestring,opcodesubarray); 
		}
	    }
	    stackDepth--;
	    theStack.pop();
	    stackItem = theStack.top();
	} while (stackDepth > 1 );
	add_assoc_zval(return_value,"result",mysubarray); 

	// Now print the memo
	ALLOC_INIT_ZVAL(mysubarray);
	array_init(mysubarray);
	int memoSize;
	memoSize = phpzope->getMemoSize();
	for (int k=0; k<memoSize; k++ )
	{
	     int result;
	     StackItem memoItem = theMemo[k];
	     for (int i = 0; i < OPCODE_COUNT; i++)
	     {
	    	Opcode *currentOpcode = myPickler->opcodes[i];
	        if (currentOpcode->opcode == memoItem.opcode)
                {
		    depth = theMemo.size();
		    ALLOC_INIT_ZVAL(opcodesubarray);
		    array_init(opcodesubarray);
	            result = (currentOpcode->opr)(opcodesubarray,&memoItem,depth);
		    sprintf(somestring,"%i",k);
		    add_assoc_zval(mysubarray,somestring,opcodesubarray); 
		}
	    }
	}

	// Now print the memo


	add_assoc_zval(return_value,"theMemo",mysubarray);
    }
} 

zend_function_entry phpzope_methods[] = {
        PHP_ME(PHPZope,  __construct,     NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
        PHP_ME(PHPZope,  returnValue,           NULL, ZEND_ACC_PUBLIC)
        PHP_ME(PHPZope,  readPickle,           NULL, ZEND_ACC_PUBLIC)
        PHP_ME(PHPZope,  setPickle,           NULL, ZEND_ACC_PUBLIC)
        PHP_ME(PHPZope,  returnPickleFile,           NULL, ZEND_ACC_PUBLIC)
        PHP_ME(PHPZope,  returnPickleString,           NULL, ZEND_ACC_PUBLIC)
	{NULL, NULL, NULL}
};

PHP_MINIT_FUNCTION(phpzope)
{
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "PHPZope", phpzope_methods);
    phpzope_ce = zend_register_internal_class(&ce TSRMLS_CC);
    phpzope_ce->create_object = phpzope_create_handler;
    memcpy(&phpzope_object_handlers,
        zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    phpzope_object_handlers.clone_obj = NULL;
    return SUCCESS;
}

zend_module_entry phpzope_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
    STANDARD_MODULE_HEADER,
#endif
    PHPZOPE_EXTNAME,
    NULL,        /* Functions */
    PHP_MINIT(phpzope),        /* MINIT */
    NULL,        /* MSHUTDOWN */
    NULL,        /* RINIT */
    NULL,        /* RSHUTDOWN */
    NULL,        /* MINFO */
#if ZEND_MODULE_API_NO >= 20010901
    PHPZOPE_EXTVER,
#endif
    STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_PHPZOPE
extern "C" {
ZEND_GET_MODULE(phpzope)
}
#endif
