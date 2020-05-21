# frozen_string_literal: true

module Chariot
  # Holds a reference to a log for a certain category and subsystem.
  class Log
    attr_reader :subsystem_name
    attr_reader :category_name

    def initialize(subsystem_name, category_name)
      @subsystem_name = subsystem_name
      @category_name = category_name
    end
  end
end
