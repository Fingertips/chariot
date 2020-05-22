# frozen_string_literal: true

require_relative 'helper'

class ChariotTest < Minitest::Test
  def test_runs
    log = Chariot.log_id('com.fngtps.rails', 'Request')
    loop do
      event_id = Chariot.topic_id(log)
      Chariot.start(log, event_id)
      Chariot.emit(log, event_id)
      Chariot.emit(log, event_id)
      Chariot.stop(log, event_id)
      sleep 1
    end
  end
end
