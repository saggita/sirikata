#include "EmersonUtil.h"
#include <antlr3.h>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#ifndef EMERSON_WHEN_PRED_COMPILE
extern pANTLR3_UINT8  EmersonParserTokenNames[];
#else
extern pANTLR3_UINT8  LexWhenPredParserTokenNames[];
#endif

keymap* emerson_sysKeys;

// Initialize emerson compiler
int emerson_init()
{
  emerson_sysKeys = new keymap();
  insertKeywords();
  return 1;
}


void insertKeywords()
{
  //cout << "insertKeywords() called\n";
  emerson_sysKeys->insert(keypair("print", "print"));
  emerson_sysKeys->insert(keypair("presences", "presences"));
}


int emerson_isImaginaryToken(pANTLR3_COMMON_TOKEN token)
{
  return 0;
}




void emerson_printRewriteStream(pANTLR3_REWRITE_RULE_TOKEN_STREAM rwStream)
{
  pANTLR3_BASE_TREE tree = (pANTLR3_BASE_TREE)rwStream->_next(rwStream);
  while(tree != NULL)
  {
      pANTLR3_COMMON_TOKEN token = tree->getToken(tree);
      if( !(emerson_isImaginaryToken(token)))
      {
          printf((const char*)token->getText(token)->chars);
      }

      tree = (pANTLR3_BASE_TREE)rwStream->_next(rwStream);
  }
  return;
}

pANTLR3_STRING emerson_printAST(pANTLR3_BASE_TREE tree)
{
  pANTLR3_STRING  string;
  ANTLR3_UINT32   i;
  ANTLR3_UINT32   n;
  pANTLR3_BASE_TREE   t;


  if(tree->children == NULL || tree->children->size(tree->children) == 0)
  {
      return	tree->toString(tree);
  }

  // THis is how you get a new string. The string is blank

  string = tree->strFactory->newRaw(tree->strFactory);

  if(tree->isNilNode(tree) == ANTLR3_FALSE)
  {
      string->append8	(string, "(");
      pANTLR3_COMMON_TOKEN token = tree->getToken(tree);
      ANTLR3_UINT32 type = token->type;

#ifndef EMERSON_WHEN_PRED_COMPILE
      string->append(string, (const char*)EmersonParserTokenNames[type]);
#else
      string->append(string, (const char*)LexWhenPredParserTokenNames[type]);
#endif
      
      string->append8(string, " ");
  }

  if(tree->children != NULL)
  {
      n = tree->children->size(tree->children);
      for	(i = 0; i < n; i++)
      {
          t   = (pANTLR3_BASE_TREE) tree->children->get(tree->children, i);
          
          if  (i > 0)
          {
              string->append8(string, " ");
          }
          string->appendS(string, emerson_printAST(t));
      }
  }
  
  if(tree->isNilNode(tree) == ANTLR3_FALSE)
  {
      string->append8(string,")");
  }
  
  return  string;

}

void emerson_createTreeMirrorImage2(pANTLR3_BASE_TREE ptr)
{

    if(ptr!= NULL && ptr->children != NULL)
    {

        ANTLR3_UINT32 n = ptr->getChildCount(ptr);
        if(n == 1)
        {
            //emerson_createTreeMirrorImage((pANTLR3_BASE_TREE)(ptr->getChild(ptr, 0)));
        }
        if(n == 2)  // should it be checked
        {
            pANTLR3_BASE_TREE right = (pANTLR3_BASE_TREE)(ptr->getChild(ptr, 1));
            //emerson_createTreeMirrorImage( (pANTLR3_BASE_TREE)(ptr->getChild(ptr, 0)));
            //emerson_createTreeMirrorImage( (pANTLR3_BASE_TREE)(ptr->getChild(ptr, 1)) );
            ptr->setChild(ptr, 1, ptr->getChild(ptr, 0));
            ptr->setChild(ptr, 0, right);
        }
    }
}


void emerson_createTreeMirrorImage(pANTLR3_BASE_TREE ptr)
{

    if(ptr!= NULL && ptr->children != NULL)
    {
        
        ANTLR3_UINT32 n = ptr->getChildCount(ptr);
        if(n == 1)
        {
            emerson_createTreeMirrorImage((pANTLR3_BASE_TREE)(ptr->getChild(ptr, 0)));
        }
        if(n == 2)  // should it be checked
        {
            pANTLR3_BASE_TREE right = (pANTLR3_BASE_TREE)(ptr->getChild(ptr, 1));
            emerson_createTreeMirrorImage( (pANTLR3_BASE_TREE)(ptr->getChild(ptr, 0)));
            emerson_createTreeMirrorImage( (pANTLR3_BASE_TREE)(ptr->getChild(ptr, 1)) );
            ptr->setChild(ptr, 1, ptr->getChild(ptr, 0));
            ptr->setChild(ptr, 0, right);
        }
    }
}


#ifndef EMERSON_WHEN_PRED_COMPILE

#include "EmersonLexer.h"
#include "EmersonParser.h"
#include "EmersonTree.h"

#else

#include "../lexWhenPred/LexWhenPredLexer.h"
#include "../lexWhenPred/LexWhenPredParser.h"
#include "../lexWhenPred/LexWhenPredTree.h"

#endif


char* emerson_compile(const char* em_script_str)
{
// printf("Trying to compile \n %s\n", em_script_str);

    pANTLR3_UINT8 str = (pANTLR3_UINT8)em_script_str;
    pANTLR3_INPUT_STREAM input = antlr3NewAsciiStringCopyStream(str, strlen(em_script_str), NULL);
    char* js_str;

#ifndef EMERSON_WHEN_PRED_COMPILE
    pEmersonLexer lxr;
    pEmersonParser psr;
    pANTLR3_COMMON_TOKEN_STREAM tstream;
    EmersonParser_program_return emersonAST;
    pANTLR3_COMMON_TREE_NODE_STREAM	nodes;
    pEmersonTree treePsr;
#else
    pLexWhenPredLexer lxr;
    pLexWhenPredParser psr;
    pANTLR3_COMMON_TOKEN_STREAM tstream;
    LexWhenPredParser_program_return emersonAST;
    pANTLR3_COMMON_TREE_NODE_STREAM	nodes;
    pLexWhenPredTree treePsr;
#endif
    
    if (input == NULL)
    {
        fprintf(stderr, "Unable to create input stream");
        exit(ANTLR3_ERR_NOMEM);
    }
#ifndef EMERSON_WHEN_PRED_COMPILE
    lxr= EmersonLexerNew(input);
#else
    lxr = LexWhenPredLexerNew(input);
#endif
    if ( lxr == NULL )
    {
        fprintf(stderr, "Unable to create the lexer due to malloc() failure1\n");
        exit(ANTLR3_ERR_NOMEM);
    }
    tstream = antlr3CommonTokenStreamSourceNew(ANTLR3_SIZE_HINT, TOKENSOURCE(lxr));
    
    if (tstream == NULL)
    {
        fprintf(stderr, "Out of memory trying to allocate token stream\n");
        exit(ANTLR3_ERR_NOMEM);
    }

#ifndef EMERSON_WHEN_PRED_COMPILE    
    psr= EmersonParserNew(tstream);  // CParserNew is generated by ANTLR3
#else
    psr= LexWhenPredParserNew(tstream);  // CParserNew is generated by ANTLR3
#endif
    if (psr == NULL)
    {
        fprintf(stderr, "Out of memory trying to allocate parser\n");
        exit(ANTLR3_ERR_NOMEM);
    }

    emersonAST = psr->program(psr);
    if (psr->pParser->rec->state->errorCount > 0)
    {
        fprintf(stderr, "The parser returned %d errors, tree walking aborted.\n", psr->pParser->rec->state->errorCount);
        
    }
    else
    {
        //printf("Emerson Tree after parsing \n%s\n", emerson_printAST(emersonAST.tree)->chars);
        nodes = antlr3CommonTreeNodeStreamNewTree(emersonAST.tree, ANTLR3_SIZE_HINT); // sIZE
                                                                                      // HINT
                                                                                      // WILL
                                                                                      // SOON
                                                                                      // BE
                                                                                      // DEPRECATED!!
#ifndef EMERSON_WHEN_PRED_COMPILE            
        treePsr= EmersonTreeNew(nodes);
#else
        treePsr= LexWhenPredTreeNew(nodes);
#endif
        
        js_str = (char*)treePsr->program(treePsr)->chars;
        nodes   ->free  (nodes);	    nodes	= NULL;
        treePsr ->free  (treePsr);	    treePsr	= NULL;
    }
    
    psr->free(psr);
    psr= NULL;
    
    tstream->free  (tstream);
    tstream= NULL;

    lxr->free(lxr);
    lxr= NULL;

    input->close (input);
    input= NULL;

    return js_str;
}

char* emerson_compile_diag(const char* em_script_str, FILE* dbg)
{
    fprintf(dbg, "Trying to compile \n %s\n", em_script_str);

    pANTLR3_UINT8 str = (pANTLR3_UINT8)em_script_str;
    pANTLR3_INPUT_STREAM input = antlr3NewAsciiStringCopyStream(str, strlen(em_script_str), NULL);
    char* js_str;

#ifndef EMERSON_WHEN_PRED_COMPILE    
    pEmersonLexer lxr;
    pEmersonParser psr;
    pANTLR3_COMMON_TOKEN_STREAM tstream;
    EmersonParser_program_return emersonAST;
    pANTLR3_COMMON_TREE_NODE_STREAM	nodes;
    pEmersonTree treePsr;
#else
    pLexWhenPredLexer lxr;
    pLexWhenPredParser psr;
    pANTLR3_COMMON_TOKEN_STREAM tstream;
    LexWhenPredParser_program_return emersonAST;
    pANTLR3_COMMON_TREE_NODE_STREAM	nodes;
    pLexWhenPredTree treePsr;
#endif
    
    
    if (input == NULL)
    {
        fprintf(stderr, "Unable to create input stream");
        fprintf(dbg, "Unable to create input stream");
        exit(ANTLR3_ERR_NOMEM);
    }
#ifndef EMERSON_WHEN_PRED_COMPILE    
    lxr = EmersonLexerNew(input);
#else
    lxr = LexWhenPredLexerNew(input);
#endif
    if ( lxr == NULL )
    {
        fprintf(stderr, "Unable to create the lexer due to malloc() failure1\n");
        fprintf(dbg, "Unable to create the lexer due to malloc() failure1\n");
        exit(ANTLR3_ERR_NOMEM);
    }
    tstream = antlr3CommonTokenStreamSourceNew(ANTLR3_SIZE_HINT, TOKENSOURCE(lxr));

    if (tstream == NULL)
    {
        fprintf(stderr, "Out of memory trying to allocate token stream\n");
        fprintf(dbg, "Out of memory trying to allocate token stream\n");
        exit(ANTLR3_ERR_NOMEM);
    }
    
#ifndef EMERSON_WHEN_PRED_COMPILE    
    psr = EmersonParserNew(tstream);  // CParserNew is generated by ANTLR3
#else
    psr = LexWhenPredParserNew(tstream);  // CParserNew is generated by ANTLR3
#endif
    
    if (psr == NULL)
    {
        fprintf(stderr, "Out of memory trying to allocate parser\n");
        fprintf(dbg, "Out of memory trying to allocate parser\n");
        exit(ANTLR3_ERR_NOMEM);
    }

    emersonAST = psr->program(psr);
    if (psr->pParser->rec->state->errorCount > 0)
    {
        fprintf(stderr, "The parser returned %d errors, tree walking aborted.\n", psr->pParser->rec->state->errorCount);
        fprintf(stderr, "The parser returned %d errors, tree walking aborted.\n", psr->pParser->rec->state->errorCount);

    }
    else
    {

        fprintf(dbg, "Emerson Tree after parsing \n%s\n", emerson_printAST(emersonAST.tree)->chars);
        nodes = antlr3CommonTreeNodeStreamNewTree(emersonAST.tree, ANTLR3_SIZE_HINT); // sIZE
                                                                                      // HINT
                                                                                      // WILL
                                                                                      // SOON
                                                                                      // BE
                                                                                      // DEPRECATED!!
#ifndef EMERSON_WHEN_PRED_COMPILE            
        treePsr= EmersonTreeNew(nodes);
#else
        treePsr= LexWhenPredTreeNew(nodes);
#endif
        
        js_str = (char*)treePsr->program(treePsr)->chars;

        fprintf(dbg, "The generated code is \n %s \n", js_str);


        nodes->free(nodes);
        nodes = NULL;
        treePsr->free(treePsr);
        treePsr	= NULL;
    }
    psr->free(psr);
    psr= NULL;
    
    tstream->free(tstream);
    tstream= NULL;

    lxr->free(lxr);
    lxr= NULL;

    input->close(input);
    input= NULL;

    return js_str;
}

char* read_file(char* filename)
{
    char * output = new char[20000];
    strcpy(output, "\n\n");
    ifstream myfile;
    myfile.open (filename);
    string line;
    if (myfile.is_open())
    {
        while (! myfile.eof() )
        {
            getline (myfile,line);
            strcat(output, line.c_str());
            strcat(output, "\n");
        }
        myfile.close();
        return output;
    }
    else
    {
        cout << "Could not open the file " << filename << endl;
    }
    
    return NULL;
}


std::string replaceAllInstances(std::string initialString, std::string toReplace, std::string toReplaceWith)
{
    size_t posToSearchFrom = 0;
    size_t finder   = initialString.find(toReplace, posToSearchFrom);

    while (finder != std::string::npos)
    {
        initialString.replace(finder,toReplace.size(), toReplaceWith);
        posToSearchFrom = finder +  toReplaceWith.size();
        finder = initialString.find(toReplace, posToSearchFrom);
    }
    return initialString;
}


std::string emerson_escapeSingleQuotes(const char* stringSequence)
{
    return replaceAllInstances(std::string(stringSequence),"'","\\'");
}





int  emerson_isAKeyword(const char* word)
{
  // Check if the keyword is one of the emerson keywords

  /*
  if( strcmp(word, "print") == 0)
		{
		  //cout << "word is print\n";

		}
	 keymap::iterator it = emerson_sysKeys->find(word);
	 //keymap::iterator it = emerson_sysKeys->find("print");
  if( it != emerson_sysKeys->end() )
		{
		  cout << "Returning 1\n";
		  return 1;
		}
		*/

  return 0;
}
