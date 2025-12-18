# Zoo

## Theme
Horror • Tactics • Story • Suspense • First-Person

## Background
You play as the night manager of a fortified zoo that imprisons “Chibis,” strange organisms with wildly different personalities, movement patterns, and countermeasures. Some appear harmless and others openly violent, but every creature must be studied, contained, and—when necessary—subdued. Over a single night you will patrol cells, respond to outages, track escapes, and decide whether to recapture or eliminate each runaway Chibi.

## Full Game Video
[![Zoo FullGame](https://img.youtube.com/vi/egldKGWGmWk/maxresdefault.jpg)](https://youtu.be/egldKGWGmWk)

## Chibi Roster
Each Chibi features a distinct behavior profile, capture approach, and knockout rule set. While the Chibis is knocked, it will not aggro other Chibis.

### Doodos — Passive
- **Behavior:** Three potato-shaped companions who hop together, bare sharp teeth when threatened, and flee if separated.
- **Capture:** Pick up one at a time. Keep them close or they panic and scatter.
- **Knockout:** Immune to standard weapons; only Berserk can knock them out. They stand back up after one minute.

### JackTheBox — Passive/Aggressive
- **Behavior:** A colorful cube that cycles through happy, peaceful, and aggressive moods, broadcasting different music for each state. Follows the player within range and deals continuous damage when aggressive. Teleports when hurt.
- **Capture:** Grab it while happy or peaceful and rush it back to its cell; gears can force a peaceful mood.
- **Knockout:** Cannot be knocked out.

### Hider — Passive
- **Behavior:** Loves hide-and-seek, remaining invisible most of the time while leaving a faint red trail. Visibility flickers faster near the player, and flees from the player when in close range. Immune to other Chibis.
- **Capture:** Must be knocked out first, then can be picked up.
- **Knockout:** One shot from the gun.

### The Blind — Passive/Aggressive
- **Behavior:** A human-like figure curled on its knees. Blind while curled but eye-focused on any sound; relentlessly attacks whatever it sees and can see in darkness. Ignores Doodos. Gunfire draws it closer.
- **Capture:** Sneak up silently, blindfold it without alerting, then lead it back.
- **Knockout:** Cannot be knocked out.

### Berserk — Aggressive
- **Behavior:** A feral beast that attacks players and nearby Chibis indiscriminately.
- **Capture:** Drag it back to its cell once it is downed.
- **Knockout:** Multiple gunshots or strikes from The Blind; wakes up after one minute.

## Nightly Timeline
- **19:30** – Wake up in the dorm at dusk, prepare food for all Chibis.
- **20:00** – Finish cooking and feed each Chibi in its cell, learning their lore and behavior.
- **20:30** – Confirm every cell is secure, then return to the dorm.
- **21:00** – Lights fail. Equip a flashlight, inspect the damaged circuit breakers, notice loose Doodos, and discover the mass escape.
- **21:30 onward** – Hunt down escaped Chibis, neutralize threats, and return them to their cells (or eliminate if necessary).

## Development Roadmap
- **Phase 1 – 11/10**
  - Project + version-control setup
  - Build core map (zoo, cells, player dorm)
  - Implement Night 1 (3 open cells) & Night 2 (all cells)
  - Basic UI foundation

- **Phase 2 – 11/17**
  - Doodos model + behavior
  - Hider model + behavior
  - Gun gameplay loop

- **Phase 3 – 11/24**
  - Berserk model + behavior
  - The Blind model

- **Phase 4 – 12/01**
  - JackTheBox model + behavior
  - Gear system
  - Crank system

- **Phase 5 – 12/15 (Final)**
  - Comprehensive testing & polish
  - Story implementation
  - Flashlight feature refinement

## Version Control
- Repository managed with GitHub for collaboration and history tracking.