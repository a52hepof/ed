#include "DenseGraph.hpp"

bool DenseGraph::remove_links(std::vector<Vertex*>::iterator base_it){
	Vertex* other;
	Vertex* base;
	Edge* edge;
	//for edges in base
	for (size_t pos_edge_base = 0; pos_edge_base < (*base_it)->getEdges().size(); pos_edge_base++){
		base=*(base_it);
		other=base->getEdges()[pos_edge_base]->getOtherVertex(*base);
		//for edge in other
		for (size_t pos_edge_other = 0; pos_edge_other < other->getEdges().size(); pos_edge_other++) {
			edge=other->getEdges()[pos_edge_other];
			//delete edge if same
			if (edge==base->getEdges()[pos_edge_base]) {
				if(! (other->removeEdge(edge))) return false;
			}
		}
	}
	return true;
}

bool DenseGraph::addVertex(Vertex* vertex){
	for (size_t i = 0; i < _vertexes.size(); i++) {
		if (_vertexes[i]==vertex) {
			return false;
		}
	}
	std::vector<Vertex*>::iterator it;
	for (it = _vertexes.begin() ; it != _vertexes.end() ; it++) {
		Edge* edge=new Edge((*it),vertex);
		(*it)->addEdge(edge);
		vertex->addEdge(edge);
	}
	_vertexes.push_back(vertex);
	return true;
}

bool DenseGraph::RemoveVertex(Vertex* vertex){
	std::vector<Vertex*>::iterator it;
	for (it=_vertexes.begin() ; it!=_vertexes.end() ; it++){
		if ( (*it) == vertex ) {
			remove_links(it);
			this->_vertexes.erase(it);
			return true;
		}
	}
	return false;
}






Tree DenseGraph::minTreePrim(){
	int timer=0;
	int totalTimer=0;

	Tree tree;
	bool isDone=false;

	float shortestDistance;
	float distance;

	Vertex* nearestVertexG;//in the graph
	Vertex* nearestVertexT;//in the tree
	Vertex* baseVertexG;
	Vertex* baseVertexT;
	Edge* shortestEdgeG;

	tree.setRoot(new Vertex(this->getVertexes()[0]->getPoint()));
	this->getVertexes()[0]->setFlag("visited");

	//searchs for the shortest edge contained in a visited vertex (one per cicle)
	while(!isDone)
	{
		timer++;
		//sets the shortestDistance and shortestEdgeG to default
		shortestDistance = -1;
		shortestEdgeG = NULL;

		//iterates trough all the vertexes
		for (size_t vertexIndex = 0; vertexIndex < this->getVertexes().size() && !isDone; vertexIndex++)
		{
			//only visited vertexes (filter)
			if (this->getVertexes()[vertexIndex]->getFlag()=="visited")
			{
				#ifdef DEBUG
				std::cout << "\t\ttesting basepoint ("<<this->getVertexes()[vertexIndex]->getPoint().getPointString()<<") flagged as <"<<this->getVertexes()[vertexIndex]->getFlag()<<">" << '\n';
				#endif

				//seeks a new shortest edge in the current vertex
				for (	size_t edgeIndex=0;\
				edgeIndex<this->getVertexes()[vertexIndex]->getEdges().size(); edgeIndex++)
				{
					distance = this	->getVertexes()[vertexIndex]\
													->getEdges()   [edgeIndex]\
													->getDistance();
					#ifdef DEBUG
					std::cout <<"testing: "<<distance<< '\n';
					#endif
					totalTimer++;
					if ( (shortestDistance > distance) || (shortestDistance == -1) )
					{
						//only not visited vertexes
						if (this->getVertexes()[vertexIndex]\
										->getEdges()   [edgeIndex]\
										->getOtherVertex(*this->getVertexes()[vertexIndex])\
										->getFlag()\
								!="visited")
						{
							baseVertexG=this->getVertexes()[vertexIndex];
							shortestDistance = distance;
							shortestEdgeG = this->getVertexes()[vertexIndex]\
																	->getEdges()   [edgeIndex];
							nearestVertexG = shortestEdgeG->getOtherVertex(*this->getVertexes()[vertexIndex]);
							#ifdef DEBUG
							std::cout <<"new shortest distance with point ("<<nearestVertexG->getPoint().getPointString()<<") < "<<shortestEdgeG->getDistance()<<">\n";
							#endif
						}else{
							#ifdef DEBUG
							std::cout << "    maked as visited, not entering" << '\n';
							#endif
						}
					}
				}
			}
		}

		//update the tree with the new shortest edge
		#ifdef DEBUG
		std::cout << "\t\t\t\t\tnearest vertex flaged as visited ("<<nearestVertexG->getPoint().getPointString()<<")\n";
		#endif
		nearestVertexT=new Vertex(nearestVertexG->getPoint());
		baseVertexT=tree.SearchVertex(baseVertexG);
		tree.addSon(baseVertexT,nearestVertexT);

		//sets the new vertex to visited
		nearestVertexG->setFlag("visited");

		//checks if there are nodes left to be visited/connected
		isDone=true;
		for (size_t j = 0; j < this->getVertexes().size() && isDone ; j++) {
			if (this->getVertexes()[j]->getFlag()!="visited"){
				isDone=false;
			}
		}

	}
	#ifdef DEBUG
	std::cout << "done in "<<timer<<" total iretations and "<<totalTimer<<" comprobations\n";
	#endif
	return tree;
}










Tree DenseGraph::minTreeKruskal(){
	int timer=0;
	int totalTimer=0;

	Tree tree;
	bool isDone=false;

	float shortestDistance;
	float distance;

	std::vector<Tree*> headsT;
	std::vector<Tree*>::iterator itHeads;
	std::vector<Tree*>::iterator itHeadsInner;

	std::vector<Vertex*> vertexG;
	std::vector<Vertex*>::iterator itVertexG;

	std::vector<Edge*> EdgesG;
	std::vector<Edge*>::iterator itEdgesG;

	Edge* edge;
	Edge* shortestEdge;

	vertexG=getVertexes();

	//initial setup
	for (itVertexG = vertexG.begin(); itVertexG != vertexG.end(); itVertexG++)
	{
		Tree* temp = new Tree();
		temp->setRoot(new Vertex((*itVertexG)->getPoint()));
		headsT.push_back(temp);
	}


	printListTrees(headsT);

	std::cout << "\n\nstarting algorithm!!!\n\n";

	connect(headsT[0]->getRoot(),headsT[1]->getRoot())

	while (!isDone && timer<10)
	{
		std::cout << "\t\titeration!!" << '\n';


		tree.tryConnect(headsT);
		timer++;
	}

	return *headsT[0];
}


void DenseGraph::printListTrees(std::vector<Tree*> headsT){
	std::vector<Tree*>::iterator itHeads;

	for (itHeads = headsT.begin(); itHeads != headsT.end(); itHeads++)
	{
		std::cout << "lista size("<< (*itHeads)->getAllVertexes().size() <<")\n\t";
		(*itHeads)->printTree();
		for (size_t i = 0; i < (*itHeads)->getAllVertexes().size(); i++) {
			if (i!=0) std::cout << "   -    "; std::cout<<(*itHeads)->getAllVertexes()[i]->getPoint().getPointString();
		}
		std::cout << "\n";
	}
}



/*	while (!isDone && timer<10)
	{
		timer++;

		shortestEdge=NULL;


		//checks for the shortest edge
		for (itVertexG = vertexG.begin(); itVertexG < vertexG.end(); itVertexG++)
		{
			EdgesG = (*itVertexG)->getEdges();
			for (itEdgesG = EdgesG.begin(); itEdgesG != EdgesG.end(); itEdgesG++)
			{
				edge = (*itEdgesG);
				bool valid=true;
				Tree t1,t2;
				t1.setRoot(new Vertex(*edge->getVertex1()));
				t2.setRoot(new Vertex(*edge->getVertex2()));

				// std::cout << "testing "<< edge->getDistance() << '\n';

				if(edge->getFlag() != "visited")
				{
					if (((shortestEdge==NULL)) || (edge->getDistance()<shortestEdge->getDistance()))
					{
						std::vector<Tree*>::iterator it;
						std::vector<Tree*>::iterator it_2;
						valid=true;
						for (it = headsT.begin(); it != headsT.end(); it++)
						{
							//if ((edge->getVertex1()->getEdges().size()>0) && (edge->getVertex2()->getEdges().size()>0))
							if (t1.areConnected(t2))
							{
								// std::cout << "not valid, marking as visited" << '\n';
								valid=false;
								edge->setFlag("visited");
							}
						}
						if (valid)
						{
							std::cout << "new shortest edge found! "<< edge->getDistance() <<"" << '\n';
							shortestEdge=edge;
						}else{
							// std::cout << "not valid!!!!!" << '\n';
						}
					}
				}else{
					// std::cout << "\t\tis visited!" << '\n';
				}
			}
		}


		//adds the edge to the tree
		if (shortestEdge==NULL)
		{
			std::cout << "ERROR NULL edge, finished" << '\n';
			break;
		}
		else
		{
			std::cout << "\t\t\tthe shortest edge is "<< shortestEdge->getDistance()<< '\n';

			Vertex* v1G=shortestEdge->getVertex1();
			Vertex* v2G=shortestEdge->getVertex2();

			if (v1G==NULL) {
				std::cout << "NULL alert-" << '\n';
			}else{
				std::cout << "v1G= "<< v1G->getPoint().getPointString() << '\n';
			}

			if (v2G==NULL) {
				std::cout << "NULL alert" << '\n';
			}else{
				std::cout << "v2G= "<< v2G->getPoint().getPointString() << "\n\n";
			}

			Vertex* v1T=NULL;
			Vertex* v2T=NULL;
			Vertex* v1T_temp=NULL;
			Vertex* v2T_temp=NULL;

			bool found=false;

			//locates v1T
			for (itHeads = headsT.begin();(itHeads != headsT.end() && !found); itHeads++)
			{
				v1T_temp=(*itHeads)->SearchVertex(v1G);
				if (v1T_temp!=NULL) {
					found=true;
					v1T=v1T_temp;
					std::cout << "v1T= "<< v1T->getPoint().getPointString() << '\n';
				}else{
					// std::cout << "NULL alert1!" << '\n';
				}
			}
			found=false;
			//locates v2T
			for (itHeads = headsT.begin();(itHeads != headsT.end() && !found); itHeads++)
			{
				v2T_temp=(*itHeads)->SearchVertex(v2G);
				if (v2T_temp!=NULL) {
					found=true;
					v2T=v2T_temp;
					std::cout << "v2T= "<< v2T->getPoint().getPointString() << '\n';
				}else{
					// std::cout << "NULL alert2!" << '\n';
				}
			}
			if (v1T==NULL || v2T==NULL) {
				std::cout << "NULL alert in v1T or v2T" << '\n';
				// if (v1T==NULL) {
				// 	Tree* t=new Tree;
				// 	t->setRoot(new Vertex(*v1G));
				// 	headsT.push_back(t);
				// }
				// if (v2T==NULL) {
				// 	Tree* t=new Tree;
				// 	t->setRoot(new Vertex(*v2G));
				// 	headsT.push_back(t);
				// }
			}else{
				std::cout << "adding edge" << '\n';
				Edge* edge_temp=new Edge(v1T,v2T);
				v1T->addEdge(edge_temp);
				v2T->addEdge(edge_temp);
			}





			shortestEdge->setFlag("visited");

		}

		std::cout << "tryConnect" << '\n';
		std::cout << "\t\t\tsize: " << headsT.size() << '\n';
		while(tree.tryConnect(headsT)){
			std::cout << "conected!!!" << '\n';
			std::cout << "\t\t\t\tnew size: " << headsT.size() << '\n';
		}


		//chechs if there are edges left
		if (headsT.size()==1) {
			std::cout << "is done!!" << '\n';
			isDone=true;
			std::cout << "final size: " << headsT[0]->getAllVertexes().size() << '\n';
		}else{
			isDone=false;
		}
	}

	return *headsT[0];*/


Tree DenseGraph::minTreeFloyd(){
	Tree tree;
	for (size_t i = 0; i < this->getVertexes().size(); i++) {
	}
	return tree;
}