# frozen_string_literal: true

require_relative '../helper'

class ChariotCoreTest < Minitest::Test
  def test_module_defined
    assert_kind_of Module, ChariotCore
  end
end
