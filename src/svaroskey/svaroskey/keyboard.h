#ifndef SVAROSKEY_KEYBOARD_H
#define SVAROSKEY_KEYBOARD_H

/* Forward decl */
struct Layout;
struct Grid;

struct Keyboard {
	struct Layout	*layout;
	struct Grid	*grid;
};

void keyboard_init(struct Keyboard *kb);
void keyboard_scan(struct Keyboard *kb);

void keyboard_set_layout(struct Keyboard *kb, struct Layout *layout);
void keyboard_set_grid(struct Keyboard *kb, struct Grid *grid);

#endif /* SVAROSKEY_KEYBOARD_H */
