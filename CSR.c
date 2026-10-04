#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_LOCATIONS 20
#define INF 999999

int num_locations = 0;
char location_names[MAX_LOCATIONS][50];
int adj_matrix[MAX_LOCATIONS][MAX_LOCATIONS];
int dist[MAX_LOCATIONS];
int parent[MAX_LOCATIONS];
bool visited[MAX_LOCATIONS];
int source_node = -1;
bool graph_entered = false;
bool shortest_path_calculated = false;


void enter_campus_graph();
void display_adjacency_matrix();
void select_source_location();
void find_shortest_distance();
void print_path(int current);
void display_shortest_paths();
void display_distances();

int main() {
    int choice;

    while (1) {
        printf("\n=========================================\n");
        printf("   CAMPUS SHORTEST ROUTE FINDER (DIJKSTRA)\n");
        printf("=========================================\n");
        printf("1. Enter Campus Graph\n");
        printf("2. Display Adjacency Matrix\n");
        printf("3. Select Source Location\n");
        printf("4. Find Shortest Distance (Run Dijkstra)\n");
        printf("5. Display Shortest Paths\n");
        printf("6. Display Distance from Source to All Locations\n");
        printf("7. Exit\n");
        printf("-----------------------------------------\n");
        printf("Enter your choice (1-7): ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Exiting program.\n");
            break;
        }

        switch (choice) {
            case 1:
                enter_campus_graph();
                break;
            case 2:
                display_adjacency_matrix();
                break;
            case 3:
                select_source_location();
                break;
            case 4:
                find_shortest_distance();
                break;
            case 5:
                display_shortest_paths();
                break;
            case 6:
                display_distances();
                break;
            case 7:
                printf("\nExiting program. Thank you!\n");
                exit(0);
            default:
                printf("\nInvalid choice! Please select an option between 1 and 7.\n");
        }
    }

    return 0;
}


void enter_campus_graph() {
    printf("\nEnter number of campus locations (max %d): ", MAX_LOCATIONS);
    scanf("%d", &num_locations);

    if (num_locations <= 0 || num_locations > MAX_LOCATIONS) {
        printf("Invalid number of locations!\n");
        num_locations = 0;
        return;
    }

    
    printf("\nEnter names for the locations:\n");
    for (int i = 0; i < num_locations; i++) {
        printf("Location %d name: ", i + 1);
        scanf(" %[^\n]", location_names[i]);
    }

    
    for (int i = 0; i < num_locations; i++) {
        for (int j = 0; j < num_locations; j++) {
            adj_matrix[i][j] = (i == j) ? 0 : INF;
        }
    }

    
    printf("\nEnter the distances between connected locations:\n");
    printf("Note: Enter -1 if there is no direct road.\n\n");

    for (int i = 0; i < num_locations; i++) {
        for (int j = i + 1; j < num_locations; j++) {
            int d;
            printf("Distance from %s to %s: ", location_names[i], location_names[j]);
            scanf("%d", &d);

            if (d < 0) {
                adj_matrix[i][j] = INF;
                adj_matrix[j][i] = INF;
            } else {
                adj_matrix[i][j] = d;
                adj_matrix[j][i] = d; 
            }
        }
    }

    graph_entered = true;
    shortest_path_calculated = false;
    source_node = -1;
    printf("\nCampus graph entered successfully!\n");
}


void display_adjacency_matrix() {
    if (!graph_entered) {
        printf("\nPlease enter the campus graph first (Option 1)!\n");
        return;
    }

    printf("\n--- Campus Adjacency Matrix ---\n\n");
    printf("%-20s", "Locations");
    for (int i = 0; i < num_locations; i++) {
        printf("%-18s", location_names[i]);
    }
    printf("\n--------------------------------------------------------------------------------\n");

    for (int i = 0; i < num_locations; i++) {
        printf("%-20s", location_names[i]);
        for (int j = 0; j < num_locations; j++) {
            if (adj_matrix[i][j] == INF) {
                printf("%-18s", "INF");
            } else {
                printf("%-18d", adj_matrix[i][j]);
            }
        }
        printf("\n");
    }
}


void select_source_location() {
    if (!graph_entered) {
        printf("\nPlease enter the campus graph first (Option 1)!\n");
        return;
    }

    printf("\nAvailable Locations:\n");
    for (int i = 0; i < num_locations; i++) {
        printf("%d. %s\n", i + 1, location_names[i]);
    }

    int choice;
    printf("\nSelect Source Location (1-%d): ", num_locations);
    scanf("%d", &choice);

    if (choice < 1 || choice > num_locations) {
        printf("Invalid selection!\n");
        return;
    }

    source_node = choice - 1;
    shortest_path_calculated = false;
    printf("\nSelected Source Location: %s\n", location_names[source_node]);
}


int min_distance_vertex() {
    int min = INF, min_index = -1;

    for (int v = 0; v < num_locations; v++) {
        if (!visited[v] && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}


void find_shortest_distance() {
    if (!graph_entered) {
        printf("\nPlease enter the campus graph first (Option 1)!\n");
        return;
    }
    if (source_node == -1) {
        printf("\nPlease select a source location first (Option 3)!\n");
        return;
    }

    for (int i = 0; i < num_locations; i++) {
        dist[i] = INF;
        visited[i] = false;
        parent[i] = -1;
    }

    dist[source_node] = 0;

    for (int count = 0; count < num_locations - 1; count++) {
        int u = min_distance_vertex();

        if (u == -1) break; 

        visited[u] = true;

        for (int v = 0; v < num_locations; v++) {
            if (!visited[v] && adj_matrix[u][v] != INF && dist[u] != INF 
                && dist[u] + adj_matrix[u][v] < dist[v]) {
                dist[v] = dist[u] + adj_matrix[u][v];
                parent[v] = u;
            }
        }
    }

    shortest_path_calculated = true;
    printf("\nDijkstra's Algorithm executed successfully from source: %s\n", location_names[source_node]);
}


void print_path(int current) {
    if (current == -1) return;
    
    print_path(parent[current]);
    
    if (current == source_node) {
        printf("%s", location_names[current]);
    } else {
        printf(" -> %s", location_names[current]);
    }
}


void display_shortest_paths() {
    if (!shortest_path_calculated) {
        printf("\nPlease calculate shortest distances first (Option 4)!\n");
        return;
    }

    printf("\n%-22s | %-18s | %s\n", "Destination", "Shortest Distance", "Shortest Path");
    printf("--------------------------------------------------------------------------------\n");

    for (int i = 0; i < num_locations; i++) {
        printf("%-22s | ", location_names[i]);
        if (dist[i] == INF) {
            printf("%-18s | No Path Available\n", "INF");
        } else {
            printf("%-18d | ", dist[i]);
            print_path(i);
            printf("\n");
        }
    }
}


void display_distances() {
    if (!shortest_path_calculated) {
        printf("\nPlease calculate shortest distances first (Option 4)!\n");
        return;
    }

    printf("\n--- Shortest Distances from Source: %s ---\n\n", location_names[source_node]);
    printf("%-25s | %s\n", "Destination Location", "Minimum Distance");
    printf("-----------------------------------------------\n");

    for (int i = 0; i < num_locations; i++) {
        if (dist[i] == INF) {
            printf("%-25s | Unreachable (INF)\n", location_names[i]);
        } else {
            printf("%-25s | %d\n", location_names[i], dist[i]);
        }
    }
}
