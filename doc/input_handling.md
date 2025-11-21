# Input handling

## Event types

The following event types are supported:

- Short press
- Long press
- Double tap
- Triple tap

## Configuration

The following values are configurable to adjust KPI for your needs:

Config | Description
-- | --
LONG_TKS | Minimum number of ticks that qualify a button press as a long press.
MTAP_TKS | Maximum number of ticks allowed between button presses in a double or triple tap.

## Event timing

The following graphs explain the timing relation between user action and event dispatching.

```txt
Short press:
ON      ___________
OFF ___|           |________________
       ^           ^      ^     ^
       |           |      |     |
       +---- LONG_TKS ----+     |
                   |            |
                   +- MTAP_TKS -+
                                |
                                +- Event!

Long press:
ON      ___________________
OFF ___|                   |_______
       ^              ^    ^
       |              |    |
       +-- LONG_TKS --+    +- Event!

Double tap:
ON      ___________            ________
OFF ___|           |__________|        |_______________
       ^           ^      ^     ^      ^            ^
       |           |      |     |      |            |
       +---- LONG_TKS ----+     |      +- MTAP_TKS -+
                   |            |                   |
                   +- MTAP_TKS -+                   +- Event!

Triple tap:
ON      ___________            ________          ________
OFF ___|           |__________|        |________|        |_____
       ^           ^      ^     ^      ^            ^    ^
       |           |      |     |      |            |    |
       +---- LONG_TKS ----+     |      +- MTAP_TKS -+    |
                   |            |                        |
                   +- MTAP_TKS -+                        +- Event!
```
