#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ex_5.h"

/****************************
 * Roey Derman
 * 322467184
 * fifth Exercise
 */

//Prints the menu
void menu() {
    printf("Welcome!\n"
            "Please select the desired option:\n"
            "1. Join the company\n"
            "2. Open a new project\n"
            "3. Join an existing project\n"
            "4. See what projects are in work\n"
            "5. See which people are in what projects\n"
            "6. Work on existing project\n"
            "7. Leave the company\n"
            "8. Exit\n");
}

// Each time we scanf string we want to clear the buffer
void clearInputBuffer(){
    char c = ' ';
    while(c != '\n')
        scanf("%c", &c);
}

// scanf chars until we get '\n', and dynamically assigned place
char *getChars(){
    clearInputBuffer();
    //char first;
    char* ch;
    int size=0;
    ch = (char*)malloc(sizeof (char));
    if(!ch) exit(1);
    scanf("%c", &ch[size]);
    if(ch[size] == '\n' || ch[size] == '\r') {
        printf("Invalid Name\n");
        free(ch);
        return NULL;
    }
    while(ch[size]!='\n') {
        size++;
        ch = (char*)realloc(ch, (size+1)*sizeof (char));
        if(!ch) exit(1);
        scanf("%c", &ch[size]);
    }
    ch[size] = '\0';
    return ch;
}


// for each project we will check if the name already in the company
int isWorkerNameExists(Worker *workers[], int workerCount, char *name){
    for(int i=0; i<workerCount;i++) {
        if(strcmp(workers[i]->name, name)==0){
            return 1;
        }
    }
    return 0;
}

// Check if the project is already in the company
int isProjectNameExists(Project *projects[], int projectCount, char *name){
    for(int i=0; i<projectCount;i++) {
        if(strcmp(projects[i]->name, name)==0){
            return 1;
        }
    }
    return 0;
}

// Check for each project if the feature exist
int isFeatureExists(FeatureNode *head, char *featureName){
    FeatureNode *temp = head;
    // Run through all the features and check if the feature name already exist
    while(temp!=NULL){
        if(strcmp(temp->feature,featureName)==0){
            return 1;
        }
        temp=temp->next;
    }
    return 0;
}

// Add worker to the company and dynamically assigned him place
void joinCompany(Worker *workers[], int *workerCount){
    char *name;
    printf("Enter the name of the new worker: ");
    name = getChars();
    if(name == NULL) {
        return;
    } else {
        if (isWorkerNameExists(workers, *workerCount, name) == 1) {
            printf("A worker with this name already exists.\n"
                   "There is not enough space in this company for both of us\n");
            free(name);
        } else {

            workers[*workerCount] = (Worker *) malloc(sizeof(Worker));
            // Check if the malloc doesn't succeed
            if (!workers[*workerCount]) exit(1);
            workers[*workerCount]->name = name;
            workers[*workerCount]->projectCount = 0;
            workers[*workerCount]->projects = NULL;
            *workerCount += 1;
        }
    }
}

// Print all the features reverse
void linked_print(FeatureNode* features){
    FeatureNode* temp = features;
    if(temp == NULL) {
        return;
    } else {
        printf("   - %s\n", temp->feature);
        // Run through all the features and print them recursively
        linked_print(temp->next);
    }
}

// Print all the project, the workers that work in them, and there features
void displayAllProjects(Project *projects[], int projectCount){
    FeatureNode *temp;
    if(projectCount ==0) {
        printf("There are no projects to display.\n");
    }else {
        for(int i=0; i<projectCount;i++) {
            printf("Project: %s\n", projects[i]->name);
            printf("  Workers in this project: \n");
            for (int j = 0; j < projects[i]->workerCount; j++) {
                printf("   - %s\n", projects[i]->workers[j]->name);
            }
            printf("  Features of the project: \n");
            // Check if there is no features
            if (projects[i]->features == NULL)
                printf("    No features\n\n");
            else {
                temp = projects[i]->features;
                linked_print(temp);
                printf("\n");
            }
        }
    }
}

// Print all the workers and the projects they are work on
void displayAllWorkers(Worker *workers[], int workerCount){
    if(workerCount ==0) {
        printf("There are no workers to display.\n");
    } else {
        for(int i=0;i<workerCount;i++) {
            printf("Worker: %s\n", workers[i]->name);
                if(workers[i]->projectCount == 0) {
                    printf("Not involved in any project.\n\n");
                }else{
                    printf("  Projects this worker is involved in: \n");
                    for (int j = 0; j < workers[i]->projectCount; j++) {
                    printf("    - %s\n\n", workers[i]->projects[j]->name);
                }
            }
        }
    }
}

// attach worker to a project
void workerJoinsProject(Worker *workers[], int workerCount, Project *projects[],
                        int projectCount){
    int choice_worker, choice_proj, bool=0;

    // Check if there are no workers in the company
    if(workerCount==0) {
        printf("There are no workers in the company yet, please join the company first.\n");
    // Check if there are no projects
    }else if (projectCount==0) {
        printf("There is not projects.");
    }else{
        printf("Select a worker to join a project: \n");
        for(int i=0;i<workerCount;i++) {
            printf("%d. %s\n", i+1, workers[i]->name);
        }
        printf("Enter the worker's number: ");
        scanf("%d", &choice_worker);
        // Check if the choice not in the range
        if(choice_worker<=0 || choice_worker > workerCount) {
            printf ("Invalid worker selection.\n");
            return;
        }
        printf("Select a project to join: \n");
        for(int i=0;i<projectCount;i++) {
            printf("%d. %s (Workers: %d)\n", i+1, projects[i]->name, projects[i]->workerCount);
        }
        printf("Enter the project's number: ");
        scanf("%d", &choice_proj);
        // Check if the choice not in the range
        if(choice_proj<=0 || choice_proj > projectCount) {
            printf ("Invalid project selection.\n");
            return;
        }
        //Check if the project has the max workers
        if(projects[choice_proj-1]->workerCount >= MAX_PROJ_WORKERS) {
            printf("Project is full.\n");
        }else {
            /* Run through all the workers in the project and check if the
               worker is already part of the project*/
            for (int i = 0; i < projects[choice_proj - 1]->workerCount; i++) {
                if (strcmp(projects[choice_proj - 1]->workers[i]->name, workers[choice_worker - 1]->name) == 0) {
                    printf("The worker is already part of the project '%s'.\n",
                           projects[choice_proj - 1]->name);
                    bool = 1;
                    break;
                }
            }
            // if the worker isn't part of the project and there is a place, add him.
            if (bool == 0) {
                projects[choice_proj - 1]->workers[projects[choice_proj - 1]->workerCount] =
                        &(*workers[choice_worker - 1]);
                projects[choice_proj - 1]->workerCount += 1;
                workers[choice_worker - 1]->projectCount += 1;
                // check if the worker doesn't have a project yet and assigned him.
                if(workers[choice_worker - 1]->projects == NULL) {
                    workers[choice_worker - 1]->projects = (Project**) malloc(sizeof (Project));
                }else {
                    workers[choice_worker - 1]->projects = (Project**)realloc(workers[choice_worker - 1]->
                            projects,(workers[choice_worker - 1]->projectCount+1)*sizeof (Project));
                }
                // check if the dynamically assigned doesn't work
                if(!workers[choice_worker - 1]->projects) exit(1);
                workers[choice_worker - 1]->projects[workers[choice_worker - 1]->projectCount-1]
                                    = projects[choice_proj - 1];
            }
        }
    }
}

// Open a new project for a specific worker
void openNewProject(Worker *workers[], int workerCount, Project *projects[],
                    int *projectCount) {
    int choice;
    char *name;
    // Check if there are no workers
    if (workerCount == 0) {
        printf("There are no workers in the company yet, please join the company first.\n");
    } else {
        printf("Who are you? Choose a number:\n");
        for (int i = 0; i < workerCount; i++) {
            printf("%d. %s\n", i + 1, workers[i]->name);
        }
        printf("Enter your choice: ");
        scanf("%d", &choice);
        // Check if the choice isn't in the range
        while (choice <= 0 || choice > workerCount) {
            printf("Invalid worker selection.\n");
            return;
        }
        printf("Enter the name of the new project: ");
        name = getChars();
        if(name==NULL) {
            return;
        }
        // check if the project for the new name is already exist
        if (isProjectNameExists(projects, *projectCount, name) == 1) {
            printf("This project already exists\n");
            printf("Better be more creative\n");
            free(name);
        } else {
            projects[*projectCount] = (Project *) malloc(sizeof(Project));
            if (!projects[*projectCount]) exit(0);
            projects[*projectCount]->workers = (Worker**) malloc(MAX_PROJ_WORKERS*sizeof (Worker));
            if (!projects[*projectCount]->workers) exit(0);
            projects[*projectCount]->workers[0] = &(*workers[choice - 1]);
            projects[*projectCount]->workerCount = 0;
            projects[*projectCount]->name = name;
            projects[*projectCount]->workerCount += 1;
            projects[*projectCount]->features = NULL;
            // Check if it is the first project of the worker and do malloc, else doing realloc
            if(workers[choice-1]->projectCount == 0) {
                workers[choice-1]->projects = (Project**) malloc (sizeof (Project*));
            } else {
                workers[choice-1]->projects = (Project**) realloc
                        (workers[choice-1]->projects,
                         (workers[choice-1]->projectCount+1)*sizeof (Project));
            }
            if(!workers[choice-1]->projects) exit(1);
            workers[choice-1]->projects[workers[choice-1]->projectCount] = &(*projects[*projectCount]);
            workers[choice-1]->projectCount+=1;
            *projectCount += 1;
        }
    }
}

// Add feature to a project
void addFeatureToProject(Project *project){
    FeatureNode* try = project->features;
    FeatureNode* new = (FeatureNode*) malloc(sizeof (FeatureNode));
    //Check if the dynamically assigned doesn't success
    if(!new) exit(1);
    printf("Enter the new feature: ");
    new->feature = getChars();
    if(new->feature == NULL) {
        return;
    } else if(isFeatureExists(project->features, new->feature) == 1) {
        printf("there is already feature like this.\n");
        free (new->feature);
        free(new);
        return;
    }
    new->next = NULL;
    // run through all the features and add new at the end
    while (try!=NULL && try->next != NULL) {
        try = try->next;
    }
    if(project->features == NULL) {
        project->features = new;
    } else {
        try->next = new;
    }
}

// remove feature from the project
void removeFeatureFromProject(Project *project){
    int index =1,remove_choice;
    FeatureNode * temp = project->features;
    FeatureNode *prev = temp;
    // check if there is no features to remove
    if(project->features == NULL) {
        printf("There is no features to remove\n");
    } else {
        printf("select a feature to remove: \n");
        printf("%d. %s\n", index, project->features->feature);
        while(temp->next != NULL) {
            index+=1;
            temp = temp->next;
            printf("%d. %s\n", index, temp->feature);

        }
        temp = project->features;
        printf("Enter your choice: ");
        scanf("%d", &remove_choice);
        if(remove_choice<0 || remove_choice>index) {
            printf("Invalid Choice");
            return;
        }
        /* run through the linked list and check if we arrive
        to the feature that we want to remove*/
        for(int i=0;i<remove_choice-1;i++) {
            prev = temp;
            temp = temp->next;
        }

        // Check if the feature already exist
        if(isFeatureExists(temp, temp->feature) == 1) {
            // Check if we want to remove the first feature
            if(project->features == temp) {
                project->features = temp->next;
                temp->next = NULL;
            } else {
                prev->next = temp->next;
                temp->next = NULL;
            }
            free(temp->feature);
            free(temp);
        } else {
            printf("There is no feature with this name");
        }
    }
}

//
void workOnProject(Worker *workers[], int workerCount, int *projectCount){
    int choice_worker, choice_proj;
    char add_remove[ADD_REMOVE];
    //Check if there is no workers in the company
    if(workerCount ==0 ) {
        printf("There are no workers in the company yet, please join the company first.\n");
    // Check if there is no projects in the company
    } else if(*projectCount ==0) {
        printf("There are no projects in the company yet, please create a project first.\n");
    } else {
        printf("Select a worker: \n");
        for(int i=0;i<workerCount;i++) {
            printf("%d. %s\n", i+1, workers[i]->name);
        }
        printf("Enter the worker's number: ");
        scanf("%d", &choice_worker);
        // Check if the choice is not in the range
        if(choice_worker<=0 || choice_worker > workerCount) {
            printf ("Invalid worker selection.\n");
            return;
        }
        // Check if the worker doesn't work on projects yet
        if(workers[choice_worker-1]->projectCount == 0) {
            printf("This worker is not involved in any projects.\n");
        } else {
            printf("Select a project: \n");
            for(int i=0;i<workers[choice_worker-1]->projectCount;i++) {
                printf("%d. %s\n", i+1, workers[choice_worker-1]->projects[i]->name);
            }
            printf("Enter the project number: ");
            scanf("%d", &choice_proj);
            //Check if the choice isn't in the range
            if(choice_proj<=0 || choice_proj > workers[choice_worker-1]->projectCount) {
                printf ("Invalid project selection.\n");
                return;
            }
            printf("Do you want to add or remove a feature? (add/remove): ");
            scanf("%s", add_remove);
            //Check if we want to add or remove features
            if(strcmp(add_remove, "add")==0) {
                addFeatureToProject(workers[choice_worker-1]->projects[choice_proj-1]);
            } else if (strcmp(add_remove, "remove")==0) {
                removeFeatureFromProject(workers[choice_worker-1]->projects[choice_proj-1]);
            }else {
                printf("Invalid choice");
                clearInputBuffer();
            }
        }
    }
}

// Free all the features of the project
void freeFeatures(Project *project) {
    FeatureNode *temp;
    FeatureNode *head = project->features;
    while(head!=NULL) {
        temp = head;
        head = head->next;
        free(temp->feature);
        free(temp);
    }
}

// Move the Project to the end of the array
int swapProjects(Project* projects[], Project* project){
    int index=0;
    Project *temp;
    while(projects[index] != project) {
        index++;
    }
    while(projects[index+1] != NULL) {
        temp = projects[index];
        projects[index] = projects[index+1];
        projects[index+1] = temp;
        index+=1;
    }
    return index;
}

// Free the project
void freeProject(Project* projects[], Project *project){
    int index;
    freeFeatures(project);
    index = swapProjects(projects, project);
    free(projects[index]->name);
    free(projects[index]->workers);
    free(projects[index]);
}

// Move the workers in the projects to the end to free him
void swap_prog_workers(Project* project, int index){
    Worker *temp;
    while(index<project->workerCount-1) {
        temp = project->workers[index];
        project->workers[index] = project->workers[index+1];
        project->workers[index+1] = temp;
        index+=1;
    }
    project->workers[index] = NULL;
}

// Move the worker to the end of the array to free him
int swap_workers(Worker* workers[], int choice_worker){
    Worker * temp;
        while(workers[choice_worker+1] != NULL) {
            temp = workers[choice_worker];
            workers[choice_worker] = workers[choice_worker+1];
            workers[choice_worker+1] = temp;
            choice_worker+=1;
        }
    return choice_worker;
}

// Free the worker that has one project
void free_worker_one_proj(Worker *workers[], int choice_worker) {
    int free_place;
    free_place = swap_workers(workers, choice_worker - 1);
    free(workers[free_place]->name);
    free(workers[free_place]);
    workers[free_place] = NULL;
}

// Free a worker
void freeWorker(Worker *workers[], Project *projects[],
                int *projectCount, int choice_worker) {
    int place_free;
        for (int i = workers[choice_worker - 1]->projectCount - 1; i >= 0; i--) {
            //Check if the worker is the only one in the project
            if (workers[choice_worker - 1]->projects[i]->workerCount == 1) {
                workers[choice_worker - 1]->projects[i]->workers[0] = NULL;
                freeProject(projects, workers[choice_worker - 1]->projects[i]);
                *projectCount -= 1;
            } else {
                /* Run through all the workers in the project and move him to the end of the array
                and equals him to null*/
                for (int j = 0; j < workers[choice_worker - 1]->projects[i]->workerCount-1 ; j++) {
                    //Check if the worker exist
                    if (strcmp(workers[choice_worker - 1]->projects[i]->workers[j]->name,
                               workers[choice_worker - 1]->name) == 0) {
                        swap_prog_workers(workers[choice_worker - 1]->projects[i], j);
                        workers[choice_worker - 1]->projects[i]->workerCount -= 1;
                    }
                }
            }
        }
        // Move the worker to the end and return the index that he is in the array
        place_free = swap_workers(workers, choice_worker - 1);
        // Free the worker
        free(workers[place_free]->name);
        free(workers[place_free]->projects);
        free(workers[place_free]);
        workers[place_free] = NULL;
}

// Free a worker that want to leave the company
void leaveCompany(Worker *workers[], int *workerCount, Project *projects[], int *projectCount){
    int choice_worker;
    //Check if there is no workers in the company
    if(*workerCount ==0) {
        printf("There are no workers in the company yet, please join the company first.\n");
    } else {
        printf("Select a worker to leave the company: \n");
        for (int i = 0; i < *workerCount; i++) {
            printf("%d. %s\n", i + 1, workers[i]->name);
        }
        printf("Enter the worker's number: ");
        scanf("%d", &choice_worker);
        // Check if the worker has onr project of more then one
         if(workers[choice_worker-1]->projectCount == 0) {
             free_worker_one_proj(workers, choice_worker);
         } else {
             freeWorker(workers, projects,
                        &(*projectCount), choice_worker);
         }
        *workerCount-=1;
    }
}


int main() {
    Project* projects[MAX_PROJECTS];
    // Equals all the members in the array to null
    for (int i = 0; i < MAX_PROJECTS; i++) {
        projects[i] = NULL;
    }
    Worker* workers[MAX_WORKERS];// array of all the workers
    // Equals all the members in the array to null
    for (int i = 0; i < MAX_WORKERS; i++) {
        workers[i] = NULL;
    }
    int counter_workers = 0;
    int proj_num = 0;
    int menu_number;

    do {
        menu();
        printf("Enter your choice: ");
        scanf("%d", &menu_number);

        // print error if the number not between the numbers of the menu
        if ((menu_number < 0 || menu_number > EXIT)) {
            printf("\nInvalid choice. Please try again.\n");
        } else {
            switch (menu_number) {
                case JOIN_COMPANY: {
                    joinCompany(workers, &counter_workers);
                    break;
                }
                case NEW_PROJECT: {
                    openNewProject(workers, counter_workers, projects, &proj_num);
                    break;
                }
                case JOIN_PROJECT: {
                    workerJoinsProject(workers, counter_workers, projects, proj_num);
                    break;
                }
                case DISPLAY_PROJ: {
                    displayAllProjects(projects, proj_num);
                    break;
                }
                case DISPLAY_WORKERS: {
                    displayAllWorkers(workers, counter_workers);
                    break;
                }
                case CHANGE_PROJ: {
                    workOnProject(workers, counter_workers, &proj_num);
                    break;
                }
                case LEAVE_COMPANY: {
                    leaveCompany(workers, &counter_workers,projects ,&proj_num);
                    break;
                }
                case EXIT: {
                    printf("Exiting...");
                    // Check for each worker if he works on one project or more
                    for(int i=0;i<counter_workers;i++) {
                        if(workers[0]->projectCount == 0){
                            free_worker_one_proj(workers, 1);
                        } else {
                            freeWorker(workers,
                                       projects, &proj_num, 1);
                        }

                    }
                    // Check if there is project that doesn't free and free them
                    for (int i = 0; i < proj_num; i++) {
                        freeProject(projects, projects[i]);
                    }
                    break;
                }
            }
        }
    }while (menu_number != EXIT);
    return 0;
}
