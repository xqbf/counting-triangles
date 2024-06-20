#include "commonfunctions.h"
#include "temporal_graph.h"
#include "online.h"
#include "kdtree.h"

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

    if(std::strcmp(argv[argc-1], "Online") == 0){
        std::cout << "Running online search..." << std::endl;
        onlineindex* Index=new onlineindex(Graph);
        double start_time = clock();
        
        online(Index, Graph, argv[2], argv[3]);
        
        std::cout << "Online search completed in " << timeFormatting((clock()-start_time)/CLOCKS_PER_SEC).str() << std::endl;
        
        delete Graph;
    }

    /*if(std::strcmp(argv[4], "Tree") == 0){
        std::cout << "Running tree index..." << std::endl;
        treeindex* Index=new treeindex(Graph);
        double start_time = clock();
        tree(Index, Graph, argv[2], argv[3]);
        std::cout << "Tree index solution completed in " << timeFormatting((clock()-start_time)/CLOCKS_PER_SEC).str() << std::endl;
        // delete Graph;
    }

    if(std::strcmp(argv[4], "Array") == 0){
        std::cout << "Running array index..." << std::endl;
        arrayindex* Index=new arrayindex(Graph);
        double start_time = clock();
        array(Index, Graph, argv[2], argv[3]);
        std::cout << "Array index solution completed in " << timeFormatting((clock()-start_time)/CLOCKS_PER_SEC).str() << std::endl;
        delete Graph;
    }

    if(std::strcmp(argv[4], "Chunk") == 0){
        std::cout << "Running chunk index..." << std::endl;
        chunkindex* Index=new chunkindex(Graph);
        double start_time = clock();
        chunk(Index, Graph, argv[2], argv[3]);
        std::cout << "Chunk index solution completed in " << timeFormatting((clock()-start_time)/CLOCKS_PER_SEC).str() << std::endl;
        delete Graph;
    }*/

    if(std::strcmp(argv[argc-1], "KD") == 0){
        std::cout << "Running kd tree index..." << std::endl;
        kdindex* Index=new kdindex(Graph);
        double start_time = clock();
        if(argc>15){
        for(int i=2;i<=10;i++){
        kd(Index, Graph, argv[i], argv[i+9]);
        std::cout << "kd tree index solution completed in " << timeFormatting((clock()-start_time)/CLOCKS_PER_SEC).str() << std::endl;
        }
        }
        else if(argc>8){
            for(int i=2;i<=5;i++){
                kd(Index,Graph,argv[i],argv[i+4]);
                std::cout << "kd tree index solution completed in " << timeFormatting((clock()-start_time)/CLOCKS_PER_SEC).str() << std::endl;
            }
        }
        else{
           for(int i=2;i<=2;i++){
        kd(Index, Graph, argv[i], argv[i+1]);
        std::cout << "kd tree index solution completed in " << timeFormatting((clock()-start_time)/CLOCKS_PER_SEC).str() << std::endl;
        } 
        }
        std::cerr<<"Over!\n";
        while(1);
        delete Graph;
    }
}
