# Adapter Pattern

## Pattern Overview

The **Adapter Pattern** makes incompatible interfaces work together by providing a wrapper that converts one interface to another. It bridges the gap between two incompatible interfaces.

## Intent

- Convert interface of a class to another expected by clients
- Allow classes with incompatible interfaces to work together
- Wrap incompatible objects
- Make legacy code work with new code

## Structure

```text
┌──────────────────────────┐
│    MediaPlayer           │ ◄────── Target Interface
├──────────────────────────┤
│                          │
├──────────────────────────┤
│ + Play(filename): void   │
│   = 0                    │
└──────────────────────────┘
         ▲
         │ implements
    ┌────┴──────────────────────┐
    │                           │
┌──────────────┐   ┌──────────────────────────┐
│ AudioPlayer  │   │ MediaAdapter             │
│(Concrete     │   │(Adapter - Wrapper)       │
│Target)       │   ├──────────────────────────┤
├──────────────┤   │ - player: unique_ptr     │
│              │   │   <AdvancedMediaPlayer>  │
├──────────────┤   ├──────────────────────────┤
│ + Play():void│   │ + Play(filename): void   │
│   {          │   │   {                      │
│     //play   │   │     player->PlayVlc()    │
│     audio    │   │     // or                │
│   }          │   │     player->PlayMkv()    │
└──────────────┘   │   }                      │
                   └────┬─────────────────────┘
                        │ uses
                        │ (wraps)
                        v
        ┌──────────────────────────────┐
        │ AdvancedMediaPlayer          │ ◄────── Adaptee Interface
        │(Incompatible Interface)      │
        ├──────────────────────────────┤
        │ + PlayVlc(): void = 0        │
        │ + PlayMkv(): void = 0        │
        └──────────────────────────────┘
                 ▲
                 │ implements
            ┌────┴─────────────────┐
            │                      │
    ┌──────────────┐      ┌──────────────┐
    │ VlcPlayer    │      │ MkvPlayer    │
    │(Concrete     │      │(Concrete     │
    │Adaptee)      │      │Adaptee)      │
    ├──────────────┤      ├──────────────┤
    │              │      │              │
    ├──────────────┤      ├──────────────┤
    │ + PlayVlc()  │      │ + PlayMkv()  │
    │ + PlayMkv()  │      │ + PlayVlc()  │
    └──────────────┘      └──────────────┘

Object Adapter Pattern (Composition):

    MediaPlayer* player = new AudioPlayer();
    player->Play("song.mp3");
    
    AdvancedMediaPlayer* vlc = new VlcPlayer();
    MediaAdapter* adapter = new MediaAdapter(vlc);
    adapter->Play("movie.vlc");  ◄── Same interface!
                                     (internally uses PlayVlc())

Adapter converts incompatible interface:

    Target Interface         Adapter             Adaptee Interface
    (MediaPlayer)            (Wrapper)           (AdvancedMediaPlayer)
    
    Play(file)  ────────────►  Play(file)  ────► PlayVlc(file)
                                            │
                                            └──► PlayMkv(file)
```

## Implementation Details

### Adapter Wrapper

```cpp
class MediaAdapter : public MediaPlayer {
  std::unique_ptr<AdvancedMediaPlayer> player_;
  
  void Play(const std::string& filename) override {
    // Convert call to adaptee interface
    player_->PlayVlc(filename);
  }
};
```

## Use Cases

- Legacy system integration
- Third-party library adaptation
- Interface conversion (API versioning)
- Component reuse with different interfaces
- Making incompatible classes work together

## Advantages

- Makes incompatible interfaces compatible
- Promotes code reuse
- No modification of original classes needed
- Single Responsibility Principle
- Open/Closed Principle

## Disadvantages

- Adds complexity
- Additional objects created
- May reduce performance slightly
- Can be overused

## Related Patterns

- **Bridge**: Similar structure, different intent
- **Decorator**: Different purpose, similar structure
- **Facade**: Simplifies complex systems
- **Proxy**: Controls access

## Key Classes

- **MediaPlayer**: Target interface
- **AdvancedMediaPlayer**: Adaptee interface
- **VlcPlayer, MkvPlayer**: Concrete adaptees
- **MediaAdapter**: Adapter class
- **AudioPlayer**: Concrete target

## Notes

- Class Adapter (inheritance) vs Object Adapter (composition)
- This implementation uses Object Adapter (composition)
- Good for integrating incompatible systems
- Alternative to modifying interfaces

## C++14 Features

- Move semantics: `MediaAdapter` constructor accepts the file type by-value and moves it into the member (`MediaAdapter(std::string file_type) : file_type_(std::move(file_type)) { ... }`). This reduces copies when callers pass temporaries or `std::move`d strings.
