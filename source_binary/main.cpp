#include "commonfunctions.h"
#include "temporal_graph.h"
#include "BTTC.h"
#include "KDT-Index.h"

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

    if(std::strcmp(argv[argc-1], "BTTC") == 0){
        std::cout << "Running BTTC..." << std::endl;
        onlineindex* Index=new onlineindex(Graph);
        double start_time = clock();
        
        online(Index, Graph, argv[2], argv[3]);
        
        std::cout << "BTTC completed in " << timeFormatting((clock()-start_time)/CLOCKS_PER_SEC).str() << std::endl;
        
        delete Graph;
    }

    if(std::strcmp(argv[argc-1], "KDT") == 0){
        std::cout << "Running KDT-Index..." << std::endl;
        kdindex* Index=new kdindex(Graph);
        double start_time = clock();
        if(argc>15){
        for(int i=2;i<=10;i++){
        kd(Index, Graph, argv[i], argv[i+9]);
        std::cout << "KDT-Index solution completed in " << timeFormatting((clock()-start_time)/CLOCKS_PER_SEC).str() << std::endl;
        }
        }
        else if(argc>8){
            for(int i=2;i<=5;i++){
                kd(Index,Graph,argv[i],argv[i+4]);
                std::cout << "KDT-Index solution completed in " << timeFormatting((clock()-start_time)/CLOCKS_PER_SEC).str() << std::endl;
            }
        }
        else{
           for(int i=2;i<=2;i++){
        kd(Index, Graph, argv[i], argv[i+1]);
        std::cout << "KDT-Index solution completed in " << timeFormatting((clock()-start_time)/CLOCKS_PER_SEC).str() << std::endl;
        } 
        }
        std::cerr<<"Over!\n";
        //while(1);
        delete Graph;
    }
}
