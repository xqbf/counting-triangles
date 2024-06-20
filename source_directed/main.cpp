#include "commonfunctions.h"
#include "temporal_graph.h"
#include "LSCc.h"
#include "onlineC.h"
#include "kdtree.h"

TemporalGraph * build(char * argv[]) {

    std::cout << "Building graph..." << std::endl;
    double start_time = clock();
    TemporalGraph * Graph = new TemporalGraph(argv[1], (char *)"Directed");
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

    if(std::strcmp(argv[4], "OnlineC") == 0){
        std::cout << "Running online search..." << std::endl;
        onlineCindex* Index=new onlineCindex(Graph);
        double start_time = clock();
        onlineC(Index, Graph, argv[2], argv[3]);
        std::cout << "Online circle search completed in " << timeFormatting((clock()-start_time)/CLOCKS_PER_SEC).str() << std::endl;
        delete Graph;
    } 

    /*if(std::strcmp(argv[4], "OnlineF") == 0){
        std::cout << "Running online search..." << std::endl;
        onlineFindex* Index=new onlineFindex(Graph);
        double start_time = clock();
        onlineF(Index, Graph, argv[2], argv[3]);
        std::cout << "Online flow search completed in " << timeFormatting((clock()-start_time)/CLOCKS_PER_SEC).str() << std::endl;
        delete Graph;
    } */

    /*if(std::strcmp(argv[argc-1], "Tree") == 0){
        std::cout << "Running tree index..." << std::endl;
        treeindex* Index=new treeindex(Graph);
        double start_time = clock();
        if(argc>5){
            for(int i=2;i<=5;i++){
                tree(Index,Graph,argv[i],argv[i+4]);
                std::cout << "Tree index solution completed in " << timeFormatting((clock()-start_time)/CLOCKS_PER_SEC).str() << std::endl;
            }

        }
        else{
        tree(Index, Graph, argv[2], argv[3]);
        std::cout << "Tree index solution completed in " << timeFormatting((clock()-start_time)/CLOCKS_PER_SEC).str() << std::endl;
        }
        //while(1);
        //delete Graph;
    }
    if(std::strcmp(argv[4], "Measure") == 0){
        std::cout << "Running measure..." << std::endl;
        measureindex* Index=new measureindex(Graph);
        double start_time = clock();
        std::cout << "Array index solution completed in " << timeFormatting((clock()-start_time)/CLOCKS_PER_SEC).str() << std::endl;
        delete Graph;
    }*/

    if(std::strcmp(argv[argc-1], "LSCc") == 0){
        std::cout << "Running LSCc index..." << std::endl;
        LSCcindex* Index=new LSCcindex(Graph);
        double start_time = clock();
        if(argc>5){
            for(int i=2;i<=10;i++){
                LSCc(Index,Graph,argv[i],argv[i+9]);
                std::cout << "LSCc index solution completed in " << timeFormatting((clock()-start_time)/CLOCKS_PER_SEC).str() << std::endl;
            }
        }
        else{
        LSCc(Index, Graph, argv[2], argv[3]);
        std::cout << "LSCc index solution completed in " << timeFormatting((clock()-start_time)/CLOCKS_PER_SEC).str() << std::endl;
        }
        //while(1);
        //delete Graph;
    }

    /*if(std::strcmp(argv[argc-1], "LSCf") == 0){
        std::cout << "Running LSCf index..." << std::endl;
        LSCfindex* Index=new LSCfindex(Graph);
        double start_time = clock();
        if(argc>5){
            for(int i=2;i<=6;i++){
                LSCf(Index,Graph,argv[i],argv[i+5]);
                std::cout << "LSCf index solution completed in " << timeFormatting((clock()-start_time)/CLOCKS_PER_SEC).str() << std::endl;
            }
        }
        else{
        LSCf(Index, Graph, argv[2], argv[3]);
        std::cout << "LSCf index solution completed in " << timeFormatting((clock()-start_time)/CLOCKS_PER_SEC).str() << std::endl;
        }
        //while(1);
        //delete Graph;
    }*/

    if(std::strcmp(argv[argc-1], "KD") == 0){
        std::cout << "Running kd tree index..." << std::endl;
        kdindex* Index=new kdindex(Graph);
        double start_time = clock();
        if(argc>5){
        for(int i=2;i<=10;i++){
        kd(Index, Graph, argv[i], argv[i+9]);
        std::cout << "kd tree index solution completed in " << timeFormatting((clock()-start_time)/CLOCKS_PER_SEC).str() << std::endl;
        }
        }
        else{
           for(int i=2;i<=2;i++){
        kd(Index, Graph, argv[i], argv[i+1]);
        std::cout << "kd tree index solution completed in " << timeFormatting((clock()-start_time)/CLOCKS_PER_SEC).str() << std::endl;
        } 
        }
        //while(1);
        delete Graph;
    }
}
