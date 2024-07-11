#include "commonfunctions.h"
#include "temporal_graph.h"
#include "online.h"
#include "measure.h"
#include "tree.h"

TemporalGraph * build(char * argv[]) {

    std::cout << "Building graph..." << std::endl;
    double start_time = clock();
    TemporalGraph * Graph = new TemporalGraph(argv[1], (char *)"Undirected");
    std::cout << "Build graph success in " << timeFormatting((clock()-start_time)/CLOCKS_PER_SEC).str() << std::endl;
    std::cout << "n = " << Graph->numOfVertices() << ", m = " << Graph->numOfEdges() << ", tmax = " << Graph->tmax << std::endl;
    return Graph;
    
}
signed main(int argc,char* argv[]){
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    
    TemporalGraph * Graph = build(argv);
    // Graph->shrink_to_fit();
    //int vertex_num = Graph->numOfVertices();

    if(std::strcmp(argv[4], "Online") == 0){
        std::cout << "Running online search..." << std::endl;
        //while(1);
        onlineindex* Index=new onlineindex(Graph);
        double start_time = clock();
        online(Index, Graph, argv[2], argv[3]);
        std::cout << "Online search completed in " << timeFormatting((clock()-start_time)/CLOCKS_PER_SEC).str() << std::endl;
        delete Graph;
    }

    if(std::strcmp(argv[4], "Measure") == 0){
        std::cout << "Running measure..." << std::endl;
        measureindex* Index=new measureindex(Graph);
        double start_time = clock();
        std::cout << "Array index solution completed in " << timeFormatting((clock()-start_time)/CLOCKS_PER_SEC).str() << std::endl;
        delete Graph;
    }

    /*if(std::strcmp(argv[argc-1], "LSC") == 0){
        std::cout << "Running LSC index..." << std::endl;
        LSCindex* Index=new LSCindex(Graph);
        double start_time = clock();
        if(argc>5){
            for(int i=2;i<=10;i++){
                LSC(Index,Graph,argv[i],argv[i+9]);
                std::cout << "LSC index solution completed in " << timeFormatting((clock()-start_time)/CLOCKS_PER_SEC).str() << std::endl;
            }
        }
        else{
        LSC(Index, Graph, argv[2], argv[3]);
        std::cout << "LSC index solution completed in " << timeFormatting((clock()-start_time)/CLOCKS_PER_SEC).str() << std::endl;
        }
        std::cerr<<"Over!\n";
        while(1);
        //delete Graph;
    }*/

    if(std::strcmp(argv[argc-1], "Tree") == 0){
        std::cout << "Running Wavelet tree index..." << std::endl;
        treeindex* Index=new treeindex(Graph);
        double start_time = clock();
        if(argc>5){
            for(int i=2;i<=10;i++){
                tree(Index,Graph,argv[i],argv[i+9]);
                std::cout << "Wavelet tree index solution completed in " << timeFormatting((clock()-start_time)/CLOCKS_PER_SEC).str() << std::endl;
            }
        }
        else{
        tree(Index, Graph, argv[2], argv[3]);
        std::cout << "Wavelet tree index solution completed in " << timeFormatting((clock()-start_time)/CLOCKS_PER_SEC).str() << std::endl;
        }
        std::cerr<<"Over!\n";
        //while(1);
        //delete Graph;
    }

    /*if(std::strcmp(argv[argc-1], "KD") == 0){
        std::cout << "Running KD index..." << std::endl;
        kdindex* Index=new kdindex(Graph);
        double start_time = clock();
        if(argc>5){
            for(int i=2;i<=10;i++){
                kd(Index,Graph,argv[i],argv[i+9]);
                std::cout << "KD index solution completed in " << timeFormatting((clock()-start_time)/CLOCKS_PER_SEC).str() << std::endl;
            }
        }
        else{
        kd(Index, Graph, argv[2], argv[3]);
        std::cout << "KD index solution completed in " << timeFormatting((clock()-start_time)/CLOCKS_PER_SEC).str() << std::endl;
        }
        std::cerr<<"Over!\n";
        //while(1);
        //delete Graph;
    }*/
}
