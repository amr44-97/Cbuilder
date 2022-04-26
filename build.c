#include "/home/amr/AM/LibStr/c/LibStr.h"
#include "/home/amr/AM/LibStr/c/error_out.h"
#include "/home/amr/AM/LibStr/c/file_handle.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <strings.h>


static void usage(char * prog_name){
    fprintf(stderr, " <usage> : %s   <Options>  <flags> \n\n",prog_name);
    Println("Options:");
    Println("--new <project_name>"ANSI_COLOR_GREEN"      create new project\n"ANSI_COLOR_RESET );
    Println("--run <project_name>"ANSI_COLOR_GREEN"      run the executable in project\n\n"ANSI_COLOR_RESET);
    Println("flags:");
    Println("--c <project_name>"ANSI_COLOR_GREEN"        C project\n"ANSI_COLOR_RESET);
    Println("--cpp <project_name>"ANSI_COLOR_GREEN"      C++ project\n"ANSI_COLOR_RESET);
    Println("--debug <project_name>"ANSI_COLOR_GREEN"    make with -g \n"ANSI_COLOR_RESET);
}



static void copy_files_obj(char* prog_name,int flag){
 
    if(prog_name == NULL){
        fprintf(stderr,ANSI_COLOR_MAGENTA "[ERROR]: no project_name passed\n" ANSI_COLOR_RESET);
        exit(EXIT_FAILURE);
    }

    file Lh,fh,ff,fL;
    const String pc = StringBuild(prog_name);
    
    if(flag == 0){
     Lh = read_file_to_string("/home/amr/AM/LibStr/c/LibStr.o");
     fh = read_file_to_string("/home/amr/AM/LibStr/c/file_handle.o");
    
    const String file_handle_dest = StringBuild("/dep/file_handle.o");
    const String LibStr_dest = StringBuild("/dep/LibStr.o");
    
    String path_f = Str_cat(pc, file_handle_dest.str); 
    String path_L = Str_cat(pc, LibStr_dest.str);

     ff = open_file(path_f.str, "wb+");
     fL = open_file(path_L.str, "wb+");

    fwrite(Lh.buf.str, 1, Lh.buf.length-1, fL.ptr);
    fwrite(fh.buf.str, 1, fh.buf.length-1, ff.ptr);

    }else if (flag == 1){
     Lh = read_file_to_string("/home/amr/AM/LibStr/cpp/LibStr.o");
     fh = read_file_to_string("/home/amr/AM/LibStr/cpp/file_handle.o");
    
    const String file_handle_dest = StringBuild("/dep/file_handle.o");
    const String LibStr_dest = StringBuild("/dep/LibStr.o");
    
    String path_f = Str_cat(pc, file_handle_dest.str); 
    String path_L = Str_cat(pc, LibStr_dest.str);

     ff = open_file(path_f.str, "wb+");
     fL = open_file(path_L.str, "wb+");

    fwrite(Lh.buf.str, 1, Lh.buf.length-1, fL.ptr);
    fwrite(fh.buf.str, 1, fh.buf.length-1, ff.ptr);




    }

    

    close_file(ff);
    close_file(fL);
    close_file(Lh);
    close_file(fh);
 
    atexit(Str_free_all);
}



static void mkproj(char * prog_name){

    DIR *di = opendir(prog_name);
    if(di != NULL){
        closedir(di);
        printf(ANSI_COLOR_BLUE "File Already Exists!!\n" ANSI_COLOR_RESET);
        return;
    }   

    if(prog_name == NULL){
        fprintf(stderr,ANSI_COLOR_MAGENTA "[ERROR]: no project_name passed\n" ANSI_COLOR_RESET);
        exit(EXIT_FAILURE);
    }
    
    const String pc = StringBuild(prog_name);
    
    mkdir(prog_name,S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    String _bin = Str_cat(pc, "/bin"); 
    mkdir(_bin.str, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    String _dep = Str_cat(pc, "/dep"); 
    mkdir(_dep.str, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    String _inc = Str_cat(pc, "/include"); 
    mkdir(_inc.str, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    String _src = Str_cat(pc, "/src"); 
    mkdir(_src.str, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    


    file Lh = read_file_to_string("/home/amr/AM/LibStr/c/LibStr.h");
    file fh = read_file_to_string("/home/amr/AM/LibStr/c/file_handle.h");
    
    const String file_handle_dest = StringBuild("/include/file_handle.h");
    const String LibStr_dest = StringBuild("/include/LibStr.h");
    
    String path_f = Str_cat(pc, file_handle_dest.str); 
    String path_L = Str_cat(pc, LibStr_dest.str);

    file ff = open_file(path_f.str, "wb+");
    file fL = open_file(path_L.str, "wb+");

    fwrite(Lh.buf.str, 1, Lh.buf.length-1, fL.ptr);
    fwrite(fh.buf.str, 1, fh.buf.length-1, ff.ptr);
 

printf(ANSI_COLOR_GREEN "Created new progect <%s>\n"ANSI_COLOR_RESET,prog_name);


    close_file(ff);
    close_file(fL);
    close_file(Lh);
    close_file(fh);
    
    atexit(Str_free_all);
}


static void prep_mkfile(char *prog_name,int comp_iler,int debug_flag){
    String pname = StringBuild(prog_name);

    String mk_f =  Str_cat(pname,"/src/Makefile");

    file fp = open_file(mk_f.str, "w+");

    String CFLAGS = StringBuild("") ;
    String CCmop = StringBuild("");
    String all = StringBuild("") ;
    String pname_c = StringBuild("") ;
    String pname_h = StringBuild("");
    String mf =  StringBuild("");


    if(comp_iler == 0)
    {
        if(debug_flag){
          CFLAGS = StringBuild("CFLAGS = -Wall -Wextra -pedantic -O2 -g \n");
        } else {
          CFLAGS = StringBuild("CFLAGS = -Wall -Wextra -pedantic -O2 \n");
        }
        
     CCmop = StringBuild("CC =gcc \n");    
     pname_c = Str_cat(pname,".c ");
     pname_h = Str_cat(pname,".h ");
     all = StringBuild(prog_name);
     Str_cat_m(&all,": ");
     Str_cat_m(&all,pname_c.str);
     Str_cat_m(&all,pname_h.str);
     
    Str_cat_m(&mf,CCmop.str);
    Str_cat_m(&mf,CFLAGS.str);
    Str_cat_m(&mf,all.str);
    Str_cat_m(&mf,"\n\t");
    Str_cat_m(&mf,"${CC} ${CFLAGS} -o ");
    Str_cat_m(&mf,pname.str);
    Str_cat_m(&mf," ");
    Str_cat_m(&mf,pname_c.str);
    Str_cat_m(&mf,"\n\t");
    Str_cat_m(&mf,"mv ");
    Str_cat_m(&mf,pname.str);
    Str_cat_m(&mf," ../bin/");


     fwrite(mf.str,1,mf.length-1, fp.ptr);

     close_file(fp);
    }else{

        if(debug_flag){
          CFLAGS = StringBuild("CFLAGS = -Wall -Wextra -pedantic -O2 -g \n");
        } else {
          CFLAGS = StringBuild("CFLAGS = -Wall -Wextra -pedantic -O2 \n");
        }
        
     CCmop = StringBuild("CC =g++ \n");    
     pname_c = Str_cat(pname,".cpp ");
     pname_h = Str_cat(pname,".h ");
     all = StringBuild(prog_name);
     Str_cat_m(&all,": ");
     Str_cat_m(&all,pname_c.str);
     Str_cat_m(&all,pname_h.str);
     
    Str_cat_m(&mf,CCmop.str);
    Str_cat_m(&mf,CFLAGS.str);
    Str_cat_m(&mf,all.str);
    Str_cat_m(&mf,"\n\t");
    Str_cat_m(&mf,"${CC} ${CFLAGS} -o ");
    Str_cat_m(&mf,pname.str);
    Str_cat_m(&mf," ");
    Str_cat_m(&mf,pname_c.str);
    Str_cat_m(&mf,"\n\t");
    Str_cat_m(&mf,"mv ");
    Str_cat_m(&mf,pname.str);
    Str_cat_m(&mf," ../bin/");

     fwrite(mf.str,1,mf.length-1, fp.ptr);

     close_file(fp);
    }

    

    atexit(Str_free_all);
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


static void prep_src(char *prog_name, int flag){

    String pname =  StringBuild(prog_name);

    String src = Str_cat(pname,"/src/");
    Str_cat_m(&src,prog_name);
    String head = Str_cat(pname,"/src/");
    Str_cat_m(&head,prog_name);
    if(flag == 0){
    Str_cat_m(&src,".c");
    }else if(flag == 1){
    Str_cat_m(&src,".cpp");
    }
    
    Str_cat_m(&head,".h");
    String src_cnt;
    if(flag == 0){
     src_cnt = StringBuild("#include \"/home/amr/AM/LibStr/c/LibStr.h\"\
\n#include \"/home/amr/AM/LibStr/c/file_handle.h\"\
\n#include <stdio.h>\n#include <stdlib.h>\n#include <string.h>\n\nint main(){\n\tprintf(\"Hello,World!\\n\");\n}");
    }else if(flag == 1){
     src_cnt = StringBuild("#include \"/home/amr/AM/LibStr/cpp/LibStr.hpp\"\
\n#include \"/home/amr/AM/LibStr/cpp/file_handle.h\"\
\n#include <stdio.h>\n#include <stdlib.h>\n#include <string>\n\nint main(){\n\tprintf(\"Hello,World!\\n\");\n}");
      
    }


    String head_h = StringBuild("__");
    Str_cat_m(&head_h,prog_name);
    Str_cat_m(&head_h,"__");
    Str_cat_m(&head_h,"H");
    Str_cat_m(&head_h,"__\n");
    String if_nf = StringBuild("#ifndef ");
    String if_df = StringBuild("#define ");
    String if_edf = StringBuild("#endif ");
    
    String hhh = StringBuild("");
    Str_cat_m(&hhh, if_nf.str) ;
    Str_cat_m(&hhh, head_h.str) ;
    Str_cat_m(&hhh, if_df.str) ;
    Str_cat_m(&hhh,head_h.str) ;
    Str_cat_m(&hhh,"\n\n\n\n") ;
    Str_cat_m(&hhh,if_edf.str) ;


    file fo = open_file(src.str, "w+");
    file fh = open_file(head.str, "w+");
    fwrite(src_cnt.str,1,src_cnt.length-1, fo.ptr);
    fwrite(hhh.str,1,hhh.length-1, fh.ptr);

    close_file(fo);
    close_file(fh);
    
    atexit(Str_free_all);
}



static void run_proj(char *prog_name){
 if(prog_name == NULL){
        fprintf(stderr,ANSI_COLOR_MAGENTA "[ERROR]: no project_name passed\n" ANSI_COLOR_RESET);
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
    atexit(Str_free_all);
}

static void def_ans(){
        fprintf(stderr,ANSI_COLOR_MAGENTA "[ERROR]: UnKnown argument \n" ANSI_COLOR_RESET);
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




if(argv[1] == NULL){
     usage(argv[0]);
     exit(1);
  }




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

   
    const String prog_name  = StringBuild(argv[2]);
    const String bin = StringBuild("/bin/");
    const String bin_path = Str_cat(bin, prog_name.str);   // create <prog_name>/bin/<prog_name(executable)>
    const String runner = Str_cat (prog_name,bin_path.str);
    
    if(new_argv1 == 0){
        
        mkproj(argv[2]);
        if(ftype_c ==0){
            copy_files_obj(argv[2],0);
            prep_src(argv[2], 0);
        }else {
            copy_files_obj(argv[2],1);
            prep_src(argv[2], 1);
        }

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
    
        run_proj(runner.str);
    
    }else {
        def_ans();
    }
     
    Str_free_all();


    return 0;
}
