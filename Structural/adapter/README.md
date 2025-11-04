# Adapter Pattern

## Pattern Overview

The **Adapter Pattern** makes incompatible interfaces work together by providing a wrapper that converts one interface to another. It bridges the gap between two incompatible interfaces.

## Intent

- Convert interface of a class to another expected by clients
- Allow classes with incompatible interfaces to work together
- Wrap incompatible objects
- Make legacy code work with new code

## Structure

```
+-----------------+
|  MediaPlayer    | (Target)
+-----------------+
      ^
      |
    +----+----------+
    |               |
+----------+  +--------------+
| Audio    |  | MediaAdapter  | (Adapter)
| Player   |  +--------------+
+----------+        |
        | uses
        v
      +---------------------+
      |AdvancedMediaPlayer  | (Adaptee)
      +---------------------+
        ^            ^
        |            |
      +----+            +----+
      |                      |
    +--------+            +---------+
    | Vlc    |            | Mkv     |
    | Player |            | Player  |
    +--------+            +---------+
```

## Implementation Details

### Adapter Wrapper

```cpp
class MediaAdapter : public MediaPlayer {
  std::unique_ptr<AdvancedMediaPlayer> player_;
  
  void play(const std::string& filename) override {
    // Convert call to adaptee interface
    player_->play_vlc(filename);
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

## Compilation & Execution

```bash
mkdir -p build
cd build
cmake ..
make
./Adapter
```

## Expected Output

```
=== Media Player with Adapter ===
Playing audio file: song.mp3
Playing VLC file: movie.vlc
Playing MKV file: video.mkv
```

## Key Classes

- **MediaPlayer**: Target interface
- **AdvancedMediaPlayer**: Adaptee interface
- **VlcPlayer, MkvPlayer**: Concrete adaptees
- **MediaAdapter**: Adapter class
- **AudioPlayer**: Concrete target

## Example Usage

```cpp
MediaAdapter vlc_adapter("vlc");
vlc_adapter.play("movie.vlc");

MediaAdapter mkv_adapter("mkv");
mkv_adapter.play("video.mkv");
```

## Notes

- Class Adapter (inheritance) vs Object Adapter (composition)
- This implementation uses Object Adapter (composition)
- Good for integrating incompatible systems
- Alternative to modifying interfaces
