# frozen_string_literal: true

require_relative 'helper'

class ChariotTest < Minitest::Test
  def test_returns_version
    refute_nil Chariot::VERSION
  end
end
