# Chariot

Ruby wrapper for `os_signposts` used to record events and intervals and show them using Xcode Instruments.

## Installation

Install a recent version of Xcode either through the developer portal or the App Store. Once installed you can start Xcode Instruments through Xcode or you can find it at:

    /Applications/Xcode.app/Contents/Applications/Instruments.app

## Usage

First you need to come up with a unique subsystem identifier so you don't get in the way of other systems or applications using the same naming as yours.

Our example is for a fictive application called ‘Yellow’.

```ruby
SUBSYSTEM = 'com.fngtps.yellow'
```

### Logs

Next we need to decide on a category and initialize a log for it. There is no overhead for creating logs other than memory allocation.

```ruby
log = Chariot::Log.new(SUBSYSTEM, "Redis Connection")
```

### Events

You can either emit an event or record the start or end of an interval. These pieces of data will later be pieced together in Instruments. Let's look at an event first.

```ruby
log.emit("Open")
```

When you are emitting large volume of events it's slightly better for performance to create a topic.

```ruby
topic = Chariot::Topic.new(log, "Open")
topic.emit
```

An event might have some important details so you can also supply them in the form a string.

```ruby
topic.emit(message: "host: #{redis.host}, port: #{redis.port}")
```

### Intervals

Recording an interval is useful because it allows us to see if certain things happen at the same time. An interval is kind of like an event with a duration so when you use the same name they will appear associated in Instruments.

```ruby
log.start("Open", message: "index: #{index}")
redis = open_connection
log.stop("Open", message: "object_id: #{redis.object_id}")
```

You can also use the block syntax so you don't have to repeat the 

```ruby
log.interval("Open") do
  redis = open_connection
end
```

Or you can combine both the topic and block approach:

```ruby
topic.interval { redis = open_connection } 
```
