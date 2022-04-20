#include "/home/amr/AM/LibStr/c/error_out.h"
#include "/home/amr/AM/LibStr/cpp/file_handle.h"
#include "/home/amr/AM/LibStr/cpp/LibStr.hpp"
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <iostream>
#include <string>
#include <vector>

static void usage(char * prog_name){
    std::cerr << " <usage> :  " << prog_name << "[Options]\n\n"; 
    std::cout << "Options:\n";
    std::cout << "--new <project_name>" ANSI_COLOR_GREEN << "      create new project\n" ANSI_COLOR_RESET ;
    std::cout << "--run <project_name>" ANSI_COLOR_GREEN << "      run the executable in project\n\n" ANSI_COLOR_RESET;
}



static void copy_files_obj( char* prog_name ){
 
    if(prog_name == NULL){
        std::cerr << ANSI_COLOR_MAGENTA "[ERROR]: no project_name passed\n" ANSI_COLOR_RESET;
        exit(EXIT_FAILURE);
    }


    const std::string pc = prog_name;


    std::string Lh = read_file_to_string("/home/amr/AM/LibStr/c/LibStr.o");
    std::string fh = read_file_to_string("/home/amr/AM/LibStr/c/file_handle.o");
    

    const std::string file_handle_dest = "/dep/file_handle.o";
    const std::string LibStr_dest = "/dep/LibStr.o";
    
    std::string path_f = pc + file_handle_dest;  

    std::string path_L = pc + LibStr_dest; 

    file ff = open_file(path_f.c_str(), "wb+");
    
    file fL = open_file(path_L.c_str(), "wb+");

    fwrite(Lh.c_str(), 1, Lh.length()-1, fL.ptr);
    fwrite(fh.c_str(), 1, fh.length()-1, ff.ptr);


    close_file(ff);
    close_file(fL);
}



static void mkproj(char * prog_name){

    DIR *di = opendir(prog_name);
    if(di != NULL){
        closedir(di);
        std::cerr << ANSI_COLOR_BLUE "File Already Exists!!\n" ANSI_COLOR_RESET;
        return;
    }   

    if(prog_name == NULL){
        fprintf(stderr,ANSI_COLOR_MAGENTA "[ERROR]: no project_name passed\n" ANSI_COLOR_RESET);
        exit(EXIT_FAILURE);
    }
    
    const std::string pc = prog_name;
    
    mkdir(prog_name,S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    std::string _bin = pc + "/bin";   //Str_cat(pc, "/bin"); 
    mkdir(_bin.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    std::string _dep = pc + "/dep"; // Str_cat(pc, "/dep"); 
    mkdir(_dep.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    std::string _inc =  pc + "/include";  //Str_cat(pc, "/include"); 
    mkdir(_inc.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    std::string _src =pc + "/src" ; // Str_cat(pc, "/src"); 
    mkdir(_src.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    


    std::string Lh = read_file_to_string("/home/amr/AM/LibStr/c/LibStr.h");
    std::string fh = read_file_to_string("/home/amr/AM/LibStr/c/file_handle.h");
    
    const std::string file_handle_dest = "/include/file_handle.h";
    const std::string LibStr_dest = "/include/LibStr.h";
    
    std::string path_f = pc + file_handle_dest;  //Str_cat(pc, file_handle_dest.str); 
    std::string path_L = pc + LibStr_dest;//Str_cat(pc, LibStr_dest.str);

    file ff = open_file(path_f.c_str(), "wb+");
    file fL = open_file(path_L.c_str(), "wb+");

    fwrite(Lh.c_str(), 1, Lh.length()-1, fL.ptr);
    fwrite(fh.c_str(), 1, fh.length()-1, ff.ptr);
 

std::cout << ANSI_COLOR_GREEN "Created new progect <" << prog_name << ">\n" ANSI_COLOR_RESET;


    close_file(ff);
    close_file(fL);
    
}


void prep_mkfile(char *prog_name,int comp_iler,int debug_flag){
    std::string pname = prog_name;

    std::string mk_f = pname + "/src/Makefile"; // Str_cat(pname,"/src/Makefile");

    file fp = open_file(mk_f.c_str(), "w+");

    std::string CFLAGS  ;
    std::string CCmop ;
    std::string all ;
    std::string pname_c  ;
    std::string pname_h ;
    std::string mf ;


    if(comp_iler == 0)
    {
        if(debug_flag){
          CFLAGS = "CFLAGS = -Wall -Wextra -pedantic -O2 -g \n";
        } else {
          CFLAGS = "CFLAGS = -Wall -Wextra -pedantic -O2 \n";
        }
        
     CCmop = "CC =gcc \n";    
     pname_c = pname + ".c " ;//Str_cat(pname,".c ");
     pname_h = pname + ".h "; //Str_cat(pname,".h ");
     all = prog_name;
     all.append(": ");
     all.append(pname_c);
     all.append(pname_h);
     
    mf = mf + CCmop + CFLAGS + all + "\n    " + "${CC} ${CFLAGS} -o " + pname + " " + pname_c;

     fwrite(mf.c_str(),1,mf.length()-1, fp.ptr);

     close_file(fp);
    }else{
   
     if(debug_flag){
          CFLAGS = "CFLAGS = -Wall -Wextra -pedantic -O2 -g \n";
        } else {
          CFLAGS = "CFLAGS = -Wall -Wextra -pedantic -O2 \n";
        }
        
     CCmop = "CC =g++ \n";    
     pname_c = pname + ".cpp " ;//Str_cat(pname,".c ");
     pname_h = pname + ".h "; //Str_cat(pname,".h ");
     all = prog_name;
     all.append(": ");
     all.append(pname_c);
     all.append(pname_h);
     
     mf = mf + CCmop + CFLAGS + all + "\n    " + "${CC} ${CFLAGS}-o " + pname + " " + pname_c;

     fwrite(mf.c_str(),1,mf.length()-1, fp.ptr);

     close_file(fp);
    }

}




/* 
 * if(ftype =  "C") -> compiler = "gcc || clang"
 * if(ftype =  "CPP") -> compiler = "g++ || clang++"
 *
 * if(f_flags = "normal") - > -Wall -Wextra -o prog_name prog_name.c
 * if(f_flags = "strict") - > -Wall -Wextra -Werror -pedantic -o prog_name prog_name.c
 * if(f_flags = "strict-optim") - > -Wall -Wextra -Werror -pedantic -O3 -o prog_name prog_name.c
 * if(f_flags = "normal-optim") - > -Wall -Wextra -O2 -o prog_name prog_name.c
 * if(f_flags = "strict-Debug") - > -Wall -Wextra  -pedantic -O2 -g -o prog_name prog_name.c
 * 
 *
 * */


static void run_proj(const char *prog_name){
 if(prog_name == NULL){
     std::cout << ANSI_COLOR_MAGENTA "[ERROR]: no project_name passed\n" ANSI_COLOR_RESET;
        exit(EXIT_FAILURE);
    }

    char *argvv[] = {NULL};
    char *argv_env[] = {NULL};
   // String p = StringBuild("/bin/");
   // String prun = Str_cat(p, prog_name);
   // const String pc = StringBuild(prog_name);
   // 
   // String prog = Str_cat(pc, prun.str);

    execve(prog_name,argvv, argv_env);
}

static void def_ans(){
    std::cerr  << ANSI_COLOR_MAGENTA "[ERROR]: UnKnown argument \n" ANSI_COLOR_RESET;
        exit(EXIT_FAILURE);
}

int get_first_arg(char *arg){
  int new_argv1 = strcmp(arg, "--new");
  int run_argv1 = strcmp(arg, "--run");
  int ret=0;
  if(new_argv1 == 0){
    ret=1;
  }else if(run_argv1 == 0){ ret= 2; }
  else {
  ret=0;
  }

  return ret;
}


int main(int argc, char** argv){

  int new_argv1 = strcmp(argv[1], "--new");
  int run_argv1 = strcmp(argv[1], "--run");
  
 int ftype_c   ;
 int ftype_cpp ;
    
 int debug_flag ;

 if(argv[3] == NULL)
    {   ftype_c =1;
        ftype_cpp=0;
    }else {
       ftype_c   = strcmp(argv[3], "--c");
       ftype_cpp = strcmp(argv[3], "--cpp");
    }

    if(argv[4] == NULL)
    {
        debug_flag =1;
    }else {
    
    debug_flag = strcmp(argv[4], "-debug");

    }

  


    if(argc < 2){
        usage(argv[0]);
        exit(EXIT_FAILURE);
    }
 
    if((new_argv1 != 0 ) && (run_argv1 !=0)){
        usage(argv[0]);
        exit(EXIT_FAILURE);
        
    } 

   
    const std::string prog_name  = argv[2];
    const std::string bin = "/bin/";
    const std::string bin_path = bin + prog_name ;
    const std::string runner = prog_name + bin_path; // Str_cat (prog_name,bin_path.str);
    
    if(new_argv1 == 0){
        
        mkproj(argv[2]);
        copy_files_obj(argv[2]);
        
        if(ftype_c == 0 ){
            if(debug_flag == 0){
                    prep_mkfile(argv[2],0,1);
            }else{
                    prep_mkfile(argv[2],0,0);
            }
        }else if(ftype_cpp == 0 ){
            if(debug_flag == 0){
                    prep_mkfile(argv[2],1,1);
            }else{
                    prep_mkfile(argv[2],1,0);
            }
        }else {
            def_ans();
            exit(-1);
        }

    } else if (run_argv1 == 0) {
    
        run_proj(runner.c_str());
    
    }else {
        def_ans();
    }
     


    return 0;
}
