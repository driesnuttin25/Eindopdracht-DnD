# D&D 5e Spell Cards Simulator

This program simulates spell cards for Dungeons and Dragons 5th edition (D&D 5e) using the D&D 5e API. The application can be invoked via the command-line interface (CLI) as follows:

```sh
Usage: SpellCards.exe spell-card-files [-s count-list] [-l level] [-h history-file]

Options:
    -s count-list        Spell slots available, the list is a sequential number of spells slots of each level that is available to the player
    -l level             Level of character
    -h history-file      Optional history file for all used spells during play
 
Example: SpellCards.exe -s 4 3 2 -l 5 fireball.json locate-object.json counterspell.json shatter.json invisibility.json blur.json identify.json vicious-mockery.json -h history.log
```

After loading the spell cards, a player can cycle through the list of spells and obtain the necessary information via the corresponding queries.

```sh
~/SpellCards$ The following queries are available:
              View spell list: Returns a list of all the available spells
              spell-name  [-at attack_type] [-ct casting_time] [-cl classes] [-co components] 
                          [-de description] [-du duration] [-r range] ...
```

A player can also choose to actually use a spell. When using a spell, it is important to mention the level at which you cast it. It is possible to cast a spell as level 1 but also as level 5, provided that the character's level is high enough and has at least one level 5 spell slot available.

```sh
~/SpellCards$ cast spell-name [-l spell-slot-level]
```

If the user wants to use a spell slot that is not available, you should mention this to the user. You should also return a list of available spell slots and suggest an available spell slot. If no level is given, the highest available spell slot is chosen.

```sh
~/SpellCards$ cast fireball -l 5
              A 5th level spell slot is not available. Do you want to use a 4th spell slot?
              The list of available spell slots is:
              * 1st level: 2
              * 2nd level: 1
              * 3th level: 0
              * 4th level: 1
              * 5th level: 0
```

If a history file is specified via the CLI, you should log the used spells as well as the used spell slots. The format in which you store this history is up to you.

## Checklist

- [x] Use appropriate data structures
- [x] Store data correctly in the appropriate members of the structures
- [x] Use pointers of the correct type
- [x] Use pointers correctly for function parameters (including call-by-reference)
- [x] Allocate memory correctly and efficiently
- [x] Avoid memory leaks and properly free allocated memory
- [ ] Correctly use the arguments to main (input and output files via flags)
- [x] Provide the correct and efficient structure for a circular linked list
- [ ] Implement functions to push, pop, and cycle the circular linked list
- [x] Store choices made in a history file using file handling
- [ ] Parse the JSON data from the file into the provided data structure
- [ ] Use the loaded file to create a playable part that tracks spell slots
- [ ] Ensure that the program works without crashing
- [ ] Make useful weekly commits on GitHub

this project is due in a couple hours and I'm practically half way done, love my life. (for legal reasons that was a joke)
