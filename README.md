# KnightsHackSubmission

Important things to note

CR = Combat Readiness
In the while loop everyone has a CRgain variable that fills up the CR variable with each iteration. Once one of them reaches 100, the person who reaches CR 100 gets a turn.
The nature of this allows for multiple turns from the same person in a row and adds strategy (ish) to deciding what to do next once you have made your move.

Debuffs:
Unfortunately I only added two debuffs, ATK Down (attack down) and Fear. 
* ATK Down decreases the attack stat of the afflicted (the player) and reduces their overall damage.
* Fear prevents the opponent from acting. Because of this you can stall certain enemies in order to make sure they don't use their attack.
* The limit to this is that this only applies to standard attack which is single target so you can only stall the one you're attacking.
* Speaking of which. All entities have 3 skills each with varying effects. For the player, they have a single target normal attack
* A heal skill and an ultimate that is avaliable from the start. If you use the other two skills that is not a normal attack they will enter cooldown
* As seen on dispaly. If you attempt to use a skill under cooldown, you'll be redirected to the single target attack.
* Unfortunately this is extremely shallow as I wanted to do more for it, but was time crunched.
* Nevertheless I am proud of what i have made.
