/* First, the standard lib includes, alphabetically ordered */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "abb.h" /* TAD abb */


void print_help(char *program_name) {
    /* Print the usage help of this program. */
    printf("Usage: %s <input file path>\n\n",
           program_name);
}

char *parse_filepath(int argc, char *argv[]) {
    /* Parse the filepath given by command line argument. */
    char *result = NULL;

    if (argc < 2) {
        print_help(argv[0]);
        exit(EXIT_FAILURE);
    }

    result = argv[1];

    return (result);
}

abb abb_from_file(const char *filepath) {
    FILE *file = NULL;
    abb read_tree;

    read_tree = abb_empty();
    file = fopen(filepath, "r");
    if (file == NULL) {
        fprintf(stderr, "File does not exist.\n");
        exit(EXIT_FAILURE);
    }
    unsigned int i = 0u;
    unsigned int size = 0u;
    int res = 0;
    res = fscanf(file, " %u ", &size);
    if (res != 1) {
        fprintf(stderr, "Invalid format.\n");
        exit(EXIT_FAILURE);
    }
    while (i < size) {
        abb_elem elem;
        res = fscanf(file," %d ", &(elem));
        if (res != 1) {
            fprintf(stderr, "Invalid array.\n");
            exit(EXIT_FAILURE);
        }
        read_tree = abb_add(read_tree, elem);

       ++i;
    }
    fclose(file);
    return read_tree;
}

void ui_help(){
    printf("\nPress:\n"
                "p to print\n"
                "a to add an element\n"
                "d to delete an element\n"
                "e to check if an element exists\n"
                "l to show the length\n"
                "r to show the root, max and min\n"
                "q to quit\n");
        
}

void user_dump_abb(abb *tree_ptr){
    abb tree = *tree_ptr;
    printf("\nwrite:\n"
            "´pre´ to pre order\n"
            "´in´ to in order\n"
            "´post´ to post order\n");
    char dump[10];
    if (fscanf(stdin, "%s", dump) != 1) {
        printf("Input error\n");
        return;
    }
    
    int res = strcmp(dump, "pre") == 0 ? ABB_PRE_ORDER : 
            strcmp(dump, "in") == 0 ? ABB_IN_ORDER : 
            strcmp(dump, "post") == 0 ? ABB_POST_ORDER : -1;
    
    if (res != -1){
        abb_dump(tree, res);
        printf("\n");
    }else{
        printf("\nfailed to print, invalid order.\n");
    }
}

abb user_add_elem(abb * tree_ptr){
    abb tree = *tree_ptr;
    printf("\nwrite an elem you want to add\n");
    abb_elem add;
    if (fscanf(stdin, "%d", &add) != 1) {
        printf("Input error\n");
        return tree;
    }
    tree = abb_add(tree, add);
    return tree;
}

abb user_delete_elem(abb * tree_ptr){
    abb tree = *tree_ptr;
    printf("\nwrite the elem you want to delete\n");
    abb_elem delete;
    if (fscanf(stdin, "%d", &delete) != 1) {
        printf("Input error\n");
        return tree;
    }
    tree = abb_remove(tree, delete);
    
    return tree;
}

void user_check_exist(abb * tree_ptr){
    abb tree = *tree_ptr;
    printf("\nwrite the elem you want to check\n");
    abb_elem check;
    if (fscanf(stdin, "%d", &check) != 1) {
        printf("Input error\n");
        return;
    }
    if (abb_exists(tree, check)){
        printf("\n´%d´ exists\n", check);

    } else{
        printf("\n´%d´ doesn't exist\n", check);
    }
    
}

int main(int argc, char *argv[]) {
    char *filepath = NULL;

    /* parse the filepath given in command line arguments */
    filepath = parse_filepath(argc, argv);

    /* parse the file to obtain an abb with the elements */
    abb tree = abb_from_file(filepath);

    /*dumping the tree*/
    abb_dump(tree, ABB_IN_ORDER);
    if (!abb_is_empty(tree)) {
        printf("\n");
        printf("raiz: %d\n minimo: %d\n maximo: %d\n", abb_root(tree),
                                                       abb_min(tree),
                                                       abb_max(tree));
    } else {
        printf("\nÁrbol vacío\n");
    }
    
    unsigned int length = abb_length(tree);

    char c = '\0';
    ui_help();
    while (c != 'q') {
        c = getchar();
        if (c != 'q'){
            switch(c) {
                case 'p': user_dump_abb(&tree); break;
                case 'a': user_add_elem(&tree); break;
                case 'd': user_delete_elem(&tree); break;
                case 'e': user_check_exist(&tree); break;
                case 'l': 
                    length = abb_length(tree);
                    printf("\nthe length of the tree is: %u\n", length);
                    break;
                case 'r': {
                    abb_elem root = abb_root(tree);
                    abb_elem min = abb_min(tree);
                    abb_elem max = abb_max(tree);
                    printf("\nraiz: %d\n minimo: %d\n maximo: %d\n", root, min, max);
                    break;
                }
                default: ui_help(); break;
            }
        }
    }

    tree = abb_destroy(tree);
    
    return (EXIT_SUCCESS);
}
