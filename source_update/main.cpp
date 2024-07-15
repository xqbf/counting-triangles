#include "commonfunctions.h"
#include "temporal_graph.h"
#include "WT-Index.h"
#include "KDT-Index.h"
//#include "LSC.h"

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

    /*if(std::strcmp(argv[4], "Online") == 0){
        std::cout << "Running online search..." << std::endl;
        onlineindex* Index=new onlineindex(Graph);
        double start_time = clock();
        online(Index, Graph, argv[2], argv[3]);
        std::cout << "Online search completed in " << timeFormatting((clock()-start_time)/CLOCKS_PER_SEC).str() << std::endl;
        delete Graph;
    }*/


    if(std::strcmp(argv[argc-1], "KDT") == 0){
        std::cout << "Running KDT-Index..." << std::endl;
        kdindex* Index=new kdindex(Graph,0.8);
        std::cout<<"Updating KDT-Index..." <<std::endl;
        Index->update(Graph,0.8);
        double start_time = clock();

        kd(Index, Graph, argv[2], argv[3]);
        std::cout << "KDT-Index solution completed in " << timeFormatting((clock()-start_time)/CLOCKS_PER_SEC).str() << std::endl;
        std::cerr << "Over!\n";
        //while(1);
        delete Graph;
    }
    
    if(std::strcmp(argv[argc-1], "WT") == 0){
        std::cout << "Running WT-Index..." << std::endl;
        treeindex* Index=new treeindex(Graph,0.8);
        std::cout<<"Updating WT-Index..." <<std::endl;
        Index->update(Graph,0.8);
        double start_time = clock();
        if(argc>5){
            for(int i=2;i<=10;i++){
                tree(Index,Graph,argv[i],argv[i+9]);
                std::cout << "WT-Index solution completed in " << timeFormatting((clock()-start_time)/CLOCKS_PER_SEC).str() << std::endl;
            }
            std::cerr << "Over!\n";
        }
        else{
        tree(Index, Graph, argv[2], argv[3]);
        std::cout << "WT-Index solution completed in " << timeFormatting((clock()-start_time)/CLOCKS_PER_SEC).str() << std::endl;
        std::cerr << "Over!\n";
        }
        //while(1);
        //delete Graph;
    }
}
