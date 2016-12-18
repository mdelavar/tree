#include <iostream>
using namespace std;


const int n = 3;
int MIN = n/2;


struct node
{
    int count;
	int data[n];

	bool hasCh;
	node *parent;
	node *childs[n + 1];

	node() {
		parent = NULL;
		count = 0;
		hasCh = false;
	}
};




node *root = NULL;

node *insert( int );
node* del(int);
bool search( int , node*& , int&);


int ins_to_null_leaf( node* , int );
void show_node_and_childs(node*);
int *make_temp(node* , int, int&b);
void del_from_normal_leaf(node*,int);

void main() {
	node *searchN = new node;
	int x;
	while (1) {

		cout  << "Chose Menu : ";
		cin >> x;
		switch (x)
		{

		case(1) :
			int data;
			cout  << "Enter num for ADD : ";
			cin >> data;

			node * ss ;
			ss = insert(data);
			show_node_and_childs(ss);
			 

			
			break;


		case(2):
		
			int x,i ;
			

			cout  << "Enter num for SEARCH : ";
			cin >> x;

			if (search(x,searchN,i)) {
				

				
				cout <<endl << i << endl;
				show_node_and_childs(searchN);
				
			} else {

				cout << "Not found!" << endl;

			}

			break;

		case(3):
		
			int y ;
			

			cout  << "Enter num for DELETE : ";
			cin >> y;
				
			node *bb;
			bb = del(y);

			if (! bb -> count == 0) {
				show_node_and_childs(bb);
			}

			break;
		default:
			break;
		}
	}
	
}


bool search( int x , node* &n , int& b) {

	node *t = root;

	while (1) {
			
			int c = t -> count;

			for (int i = 0 ; i < c ; i ++ ) {

				if (t -> data[i] == x) {
					n = t;
					b = i;
					return true;
				}

			}

			if (t -> hasCh) { 
				if (x < t -> data[0]) {t = t -> childs[0];}
				else if (x > t -> data[c-1]) { t = t -> childs[c];}
				else {
					for (int i = 0; i< t -> count  ; i++) {
						if ( t -> data[i+1] != NULL && x > t -> data[i] && x < t -> data[i+1]) {

							t = t -> childs[i+1];
							break;

						}

						
					}
				}
			}

			else {
				n = NULL;
				return false;

			}
		}

}

node *insert( int a ) {

	if ( root == NULL) {
		root = new node;
		root -> data[0] = a;
		root -> count = 1; 
		return root;
	} else if ( !root -> hasCh && root -> count < n) {
		ins_to_null_leaf(root,a);
	
		return root;
	} else if ( !root -> hasCh && root -> count == n) {

		int b;
		int *temp = make_temp(root,a,b);

		
		int j ;
		int p = (n-1) / 2;
		node * t = new node;
		t -> data[0] = temp[p];
		t -> count = 1;
		t -> childs[0] = new node;
		t -> childs[0] -> parent = t;
		t -> childs[1] = new node;
		t -> childs[1] -> parent = t;

		t -> hasCh = true;

		j = 0;
		for (int i = 0; i < p ; i ++) {

			t -> childs[0] -> data[j] = temp[i];
			t -> childs[0] -> count ++;
			j ++;

		}


	    j = 0;
		for (int i = p+1; i < n+1 ; i ++) {

			t -> childs[1] -> data[j] = temp[i];
			t -> childs[1] -> count ++;
			j ++;

		}

		delete root;
		root = t;
		return root;


	} else if (root -> hasCh) {
		node *t = root;
		while (t -> hasCh) {
			int j = 1;
			int c = t -> count;
			if (a <= t -> data[0]) {t = t -> childs[0];}
			else if (a > t -> data[c-1]) { t = t -> childs[c];}
			else {
				for (int i = 0; i< t -> count ; i++) {
					if ( t -> data[j] != NULL && a > t -> data[i] && a <= t -> data[j]) {

						t = t -> childs[j];
						break;

					}

					j++;
				}
			}
		}
			if ( t -> count < n) {
				ins_to_null_leaf(t,a);
				return t;

			} else if (t -> count == n && t -> parent -> count < n) {
			    int c = t -> parent -> count;
				node *nfd = t; // node for delete
				node *pa = t -> parent; 

				int p = (n-1) / 2; // middle
				int b,j;
				int *temp = make_temp(t,a,b);

				node *ch1 = new node;
				node *ch2 = new node;

				ch1 -> parent =  pa;
				ch2 -> parent =  pa;


				j = 0;
				for (int i = 0; i < p ; i ++) {

					ch1 -> data[j] = temp[i];
					ch1 -> count ++;
					j ++;

				}


				j = 0;
				for (int i = p+1; i < n+1 ; i ++) {

					ch2 -> data[j] = temp[i];
					ch2 -> count ++;
					j ++;

				}

				int ch = ins_to_null_leaf(pa,temp[p]); // add middle to parent
				
				node *chs[n+1];
				

				j = 0;
				for (int i = 0; i < c + 1; i ++) {

					if ( i == ch )  {
						chs[j] = ch1;
						chs[j+1] = ch2;
						j ++;
					} else {

						chs[j] = pa -> childs[i];
						

					}
					j++;
				}
				for (int i = 0; i < c + 2; i++) {
					pa -> childs[i] = chs[i];
				}
				delete nfd;

				
				
				return ch1 -> parent;

			} else if ( t -> count == n && t -> parent -> count == n) {
				
				int b,m = a;
				node *chs[n+2];
				bool havCH = false;

				while (1)
				{

					if (t == root && t -> count == n) {
						node *ch1 = new node;
						node *ch2 = new node;
						node *ch3 = new node;

						int b,j,p = (n-1) / 2;;
						int *temp = make_temp(t,m,b);

						m = temp[p];


						j = 0;
						for (int i = 0; i < p ; i ++) {

							ch2 -> data[j] = temp[i];
							ch2 -> count ++;
							j ++;

						}


						j = 0;
						for (int i = p+1; i < n+1 ; i ++) {

							ch3 -> data[j] = temp[i];
							ch3 -> count ++;
							j ++;
						}


						int cn = (n+2) / 2;
						if ( havCH == true ) {
							j = 0;
							for ( int i = 0 ; i < cn ; i++) {
								chs[i] -> parent = ch2;
								ch2 -> childs[j] = chs[i];
								j++;
							}

							j = 0;
							for ( int i = cn ; i < t -> count + 2 ; i++) {
								chs[i] -> parent = ch3;
								ch3 -> childs[j] = chs[i];

								j++;
							}

							ch2 -> hasCh = true;
							ch3 -> hasCh = true;

							ch2 -> parent = ch1;
							ch3 -> parent = ch1;
							ch1 -> hasCh = true;

							ch1 -> childs[0] = ch2;
							ch1 -> childs[1] = ch3;
						}

						ins_to_null_leaf(ch1,m);

						root = ch1;

						return root;
						
					} else if (t -> count < n) {

						int a = ins_to_null_leaf(t,m);
						for (int i = 0; i < t -> count + 1; i++) {
							chs[i] -> parent = t;
							t -> childs[i] = chs[i];
						}	
						return t;


					} else {

						
						int *temp = make_temp(t,m,b);

						int j,p = (n-1) / 2;

						m = temp[p];


						node *ch1 = new node;
						node *ch2 = new node;
						

						j = 0;
						for (int i = 0; i < p ; i ++) {

							ch1 -> data[j] = temp[i];
							ch1 -> count ++;
							j ++;

						}


						j = 0;
						for (int i = p+1; i < n+1 ; i ++) {

							ch2 -> data[j] = temp[i];
							ch2 -> count ++;
							j ++;
						}

						int cn = (n+2) / 2;
						if ( havCH == true ) {
							j = 0;
							for ( int i = 0 ; i < cn ; i++) {
								chs[i] -> parent = ch1;
								ch1 -> childs[j] = chs[i];
								j++;
							}

							j = 0;
							for ( int i = cn ; i < t -> count + 2 ; i++) {
								chs[i] -> parent = ch2;
								ch2 -> childs[j] = chs[i];

								j++;
							}

							ch1 -> hasCh = true;
							ch2 -> hasCh = true;

						}


						
						


						j = 0;

						make_temp(t -> parent,m,b);
						for (int i = 0; i < t -> parent -> count + 1; i ++) {

							if ( i == b )  {
								chs[j] = ch1;
								chs[j+1] = ch2;
								j ++;
							} else {

								chs[j] = t -> parent -> childs[i];
						
							}
							j++;
						}
						havCH = true;

						t = t-> parent;
					}
				}
			}
		}
	return new node;
}  



node* del(int a) {

	int b,cp = 0,m = a;
	
	node* nd;
	
	bool hCh = false;



	if (search(m,nd,b)) {

		if (nd -> hasCh) hCh = true;

		for (int i = 0; i <= nd -> parent -> count; i++ ) {
			if ( nd -> parent -> childs[i] == nd ) {cp = i;cout << "ss : " <<  cp << endl;}
		}


		if (nd != root) {
			if (hCh) {
				// if Not leaf


			} else {
				// If leaf
				if ( nd -> count > MIN) {

					// if normal leaf
					del_from_normal_leaf(nd,m);
					return nd;
				} else {
					// if not normal leaf

					if(nd -> parent -> childs[cp - 1] -> count > MIN) {
						// if left sibling is a normal leaf

					} else if (nd -> parent -> childs[cp + 1] -> count > MIN) {
						// if right sibling is a normal leaf

					} else {
						// if right and left siblings are not normal leafs

						if ( nd -> parent -> count > MIN ) {
							// if parent is a normal node

						} else {

							// if parent is not a normal node



						}

					}
				}

			}
		}

	} else {

		cout << "Not found value for delete !" << endl;

	}

	return new node;
}



int ins_to_null_leaf( node* r,int a ) {
	
		int c = r -> count;
		r -> count ++;
		if ( a >= r -> data[c-1] ) {
			r -> data[c] = a;
			
		} else {
			for (int i = 0; i < c ; i++) {
				if ( a <= r -> data[i] ) {

					for (int j = c ; j > i ; j -- ) {
						r -> data[j] = r -> data[j-1]; 
					}

					r -> data[i] = a;
					return i;
				}
				
			}
		}

}

int *make_temp(node *nd, int a,int&b) {


	int *temp = new int[n+1];
		int j = 0;
		if ( a > nd -> data[nd -> count -1 ] ){
			
			temp[nd -> count] = a;
			b = nd -> count;

		}
		for ( int i = 0; i < n; i++) {

			if (nd -> data[i] < a ) {
				temp[j] = nd -> data[i];
				j++;
			} else if (a <= nd -> data[i]){
				b = j;
				temp[j] = a;
				for ( int p = i; p < n; p++) {
					j ++;
					temp[j] = nd -> data[p];
				}
				break;
				
			}
		}

	return temp;
}



void show_node_and_childs(node* ss) {

	 cout << "\n\n** Node **" << endl;
			for (int i = 0; i < ss -> count; i++) {

				cout << ss ->data[i] << "  ";
			}
			
			cout << endl;

			if ( ss -> hasCh) {

				for ( int j = 0; j < ss -> count + 1 ; j ++) {
					cout << "\nch : "<< j << endl;
		
					for (int i = 0; i < ss -> childs[j] -> count; i++) {

						cout << ss -> childs[j] -> data[i]  << "  ";
						
					}
					
					cout << endl;

					

				}
				
			}
			cout << endl;
			cout << endl;
			cout << endl;


}

void del_from_normal_leaf(node *a,int x) {

	
	

	for (int i = 0 ; i < a -> count ; i++) {
		if (a -> data[i] == x) {
			if ( !i == a -> count - 1) {

				for (int j = i ; j < a -> count - 1; j++) {

					a -> data[j] = a -> data[j+1];
				}

				a -> count -= 1;
				return;
			} else {
				a -> count -= 1;
				return;
			}
			

		}


	}
	a -> count -= 1;


}