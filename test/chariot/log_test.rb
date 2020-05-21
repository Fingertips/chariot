# frozen_string_literal: true

require_relative '../helper'

module Chariot
  class LogTest < Minitest::Test
    def test_initialize
      subsystem_name = 'com.fngtps.yellow'
      category_name = 'Redis Connection'
      log = Chariot::Log.new(subsystem_name, category_name)
      assert_equal subsystem_name, log.subsystem_name
      assert_equal category_name, log.category_name
    end
  end
end
