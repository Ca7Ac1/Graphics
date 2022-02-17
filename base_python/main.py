from display import *
from draw import *
from matrix import *

screen = new_screen()
color = [ 0, 0, 0 ]
m1 = new_matrix()
m2 = []
edges = []

print('\nTesting add_edge. Adding (1, 2, 3), (4, 5, 6) m2 =')
add_edge(m2, 1, 2, 3, 4, 5, 6)
print_matrix( m2 )

print('Testing ident. m1 = ')
ident(m1)
print_matrix( m1 )

print('\nTesting matrix_mult. m1 * m2 =')
matrix_mult(m1, m2)
print_matrix(m2)

m1 = [];
add_edge(m1, 1, 2, 3, 4, 5, 6)
add_edge(m1, 7, 8, 9, 10, 11, 12)
print("\nTesting Matrix mult. m1 =")
print_matrix(m1)
print("\nTesting Matrix mult. m1 * m2 =")
matrix_mult(m1, m2);
print_matrix(m2);

add_edge(edges, 50, 450, 0, 100, 450, 0)
add_edge(edges, 50, 450, 0, 50, 400, 0)
add_edge(edges, 100, 450, 0, 100, 400, 0)
add_edge(edges, 100, 400, 0, 50, 400, 0)

add_edge(edges, 200, 450, 0, 250, 450, 0)
add_edge(edges, 200, 450, 0, 200, 400, 0)
add_edge(edges, 250, 450, 0, 250, 400, 0)
add_edge(edges, 250, 400, 0, 200, 400, 0)

add_edge(edges, 150, 400, 0, 130, 360, 0)
add_edge(edges, 150, 400, 0, 170, 360, 0)
add_edge(edges, 130, 360, 0, 170, 360, 0)

add_edge(edges, 100, 340, 0, 200, 340, 0)
add_edge(edges, 100, 320, 0, 200, 320, 0)
add_edge(edges, 100, 340, 0, 100, 320, 0)
add_edge(edges, 200, 340, 0, 200, 320, 0)  

draw_lines( edges, screen, color )
save_extension(screen, "bob.png")
display(screen)
