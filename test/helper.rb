# frozen_string_literal: true

require 'minitest/autorun'

%w[ext lib].each do |path|
  $LOAD_PATH.unshift(File.expand_path("../#{path}", __dir__))
end

require 'chariot'
