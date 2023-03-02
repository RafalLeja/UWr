#include<stdio.h>
#include<stdbool.h>

typedef struct list {
    int val;
    struct list *next;
} list;

typedef struct link_list {
    struct list *head, *tail;
} link_list;


list *make(int wart) {
    list *pom = (list *)malloc(sizeof(list));
    pom->val = wart;
    pom->next = NULL;
    return pom;
}

void make_neigh(link_list *lista, int val) {
    if(lista->head == NULL){
        list *tmp = make(val);
        lista->tail = tmp;
        lista->head = tmp;
    }
    else{
        list *tmp = make(val);
        lista->tail->next = tmp;
        lista->tail = lista->tail->next;
    }
}

int pop(link_list *lista) {
    if(lista->head == lista->tail){
        lista -> head = NULL;
        lista -> tail = NULL;
        int a = lista->head->val;
        free(lista->tail);
        return a;
    }
    else{
        int a = lista->head->val;
        list *tmp = lista->head;
        lista->head = lista->head->next;
        free(tmp);
        return a;
    } 
}

bool vis[103];

link_list *neigh[103];

int tab[100][100];

void zad1_m_to_l(int m){ //m - liczba wierzcholkow
    for(int i = 0; i < m; i++){ //pamieciowa n^2    czasowa n^2
        for(int j = 0; j < m; j++){
            if(tab[i][j] == 1)
                make_neigh(neigh[i], j);
        }
    }
}

void zad1_l_to_m(int m){ //m - liczba wierzcholkow
    for(int i = 0; i < m; i++){ //pamieciowa n^2    czasowa m+n
        list *pom = neigh[i]->head;
        while(pom != NULL){
            tab[i][pom->val] = 1;
            pom = pom->next;
        }
    }
}

void dfs(int beg){
    vis[beg] = 1;
    list *pom = neigh[beg]->head;
    while(pom != NULL){
        if(!vis[pom->val]){
            dfs(pom->val);
        }     
        pom = pom->next;
    }
}

 
void zeruj(int n){
    for(int i = 0; i < n; i++){
        vis[i] = 0;
    }
}

void del_vertex(int a, int b){
    list *prev = neigh[a]->head, *curr = prev->next;
    if(prev->val == b){
        int trash = pop(neigh[a]);
    }
    else{
        while(curr->next != NULL && curr->val != b){
            prev = curr;
            curr = curr->next;
        }
        prev->next = curr->next;
        free(curr);
    }
}

bool zad2(int u, int v){// n - ilosc wierzcholkow
    del_vertex(u, v); // n - zlozonosc pamieciowa  n+m bo graf
    del_vertex(v, u);
    dfs(u);
    if(vis[v] == 1)
        return 0;
    return 1;
}

bool zad3(int n){
    // pamieciowka O(n+m)
    for(int i = 0; i < n; i++){
        list *pom = neigh[i]->head;
        while(pom != NULL){
            zeruj(103);
            if(zad2(i, pom->val) == 1)
                return 1;
            make_neigh(neigh[i], pom->val);
            make_neigh(neigh[pom->val], i);
            pom = pom->next;

        }
    }
    return 0;
}



void zad45(int u, int v, int n){
    int parent[n]; //czasowa n+m bo bfs, pamieciowa n+m bo graf
    zeruj(103);
    link_list *q = NULL;
    vis[v] = 1;
    make_neigh(q, v);
    while(q->head != NULL){
        int h = pop(q);
        list *pom = neigh[h]->head;
        while(pom != NULL){
            if(!vis[pom->val]){
                vis[pom->val] = 1;
                parent[pom->val] = h;
                make_neigh(q, pom->val);
            }
        }
    }
    if(!vis[u]){
        printf("-1");
    }
    else{
        int tmp = u;
        while(parent[tmp] != v){
            printf("%d -> ", tmp);
            tmp = parent[tmp];
        }
        printf("%d", v);
    }
}

void dfs_ale_umie_matme(int beg, int *counter){
    vis[beg] = 1;
    list *pom = neigh[beg]->head;
    while(pom != NULL){
        if(!vis[pom->val]){
            *counter = *counter + 1;
            dfs_ale_umie_matme(pom->val, counter);
        }     
        pom = pom->next;
    }
}

bool zad6(int v){
    zeruj(103);
    list *pom = neigh[v]->head;
    if(pom == NULL)
        return 0;
    int pre = 1, post = 1, los_sas = pom->val;
    dfs_ale_umie_matme(v, &pre);
    while(pom != NULL){
        // del_vertex(v, pom->val);
        del_vertex(pom->val, v);
        pom = pom->next;
    }
    zeruj(103);
    dfs_ale_umie_matme(los_sas, &post);
    if(post == pre - 1)
        return 0;
    return 1;
}

void dfs2(int beg, int parent[], int *cykbeg, int *cykend){
    vis[beg] = 1;
    list *pom = neigh[beg]->head;
    while(pom != NULL){
        if(vis[pom->val] && parent[beg] != pom->val){
            *cykend = pom->val;
            *cykbeg = beg;
            return;
        }           
        if(!vis[pom->val]){
            parent[pom->val] = beg;
            dfs2(pom->val, parent, cykbeg, cykend);
        }     
        pom = pom->next;
    }
}

void zad7(int n){
    zeruj(103);
    link_list *odp;
    for(int i = 0; i < n; i++){
        if(!vis[i]){
            make_neigh(odp, i);
            vis[i] = 1;
            list *pom = neigh[i]->head;
            while(pom != NULL){
                vis[pom->val] = 1;
                pom = pom->next;
            }
        }
    }
}

void zad8(int n){
    int parent[n];
    zeruj(103);
    int parent[103], cykbeg = -1, cykend = -1;
    for(int i = 1 ; i <= n; i++){
        if(!vis[i]){
            parent[i] = i;
            dfs2(i, parent, &cykbeg, &cykend);
            if(cykbeg != cykend)
                break;
        } 
    }  
    if(cykbeg == cykend)
        printf("NIE  MA CYKLU");
    else{
        int tmp = cykbeg;
        while(parent[tmp] != cykend){
            printf("%d -> ", tmp);
            tmp = parent[tmp];
        }
        printf("%d", cykend);
    }

}