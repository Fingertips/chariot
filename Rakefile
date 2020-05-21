# frozen_string_literal: true

require 'rdoc/task'

$LOAD_PATH.unshift(File.expand_path('ext', __dir__))

task default: :test
task compile: 'extconf:compile'

desc 'Run all tests'
task test: :compile do
  Dir[File.dirname(__FILE__) + '/test/**/*_test.rb'].each do |file|
    ruby file
  end
end

task :clean do
  crap = '*.{bundle,so,o,obj,log}'
  ['*.gem', "ext/**/#{crap}", 'ext/**/Makefile'].each do |glob|
    Dir.glob(glob).each do |file|
      rm(file)
    end
  end
end

namespace :extconf do
  task :makefile do
    Dir.chdir('ext') do
      ruby 'extconf.rb'
    end
  end

  task make: :makefile do
    Dir.chdir('ext') do
      sh(RUBY_PLATFORM =~ /win32/ ? 'nmake' : 'make') do |ok, _res|
        unless ok
          require 'fileutils'
          FileUtils.rm_rf(Dir.glob('*.{so,o,dll,bundle}'))
        end
      end
    end
  end

  desc 'Compile the Ruby extension'
  task compile: :make do
    if Dir.glob('ext/*.{o,so,dll}').empty?
      warn('Failed to build ext.')
      exit(1)
    end
  end
end

namespace :docs do
  Rake::RDocTask.new('generate') do |rdoc|
    rdoc.title = 'Chariot'
    rdoc.main = 'README.md'
    rdoc.rdoc_files.include('README.md', 'ext/chariot_core.c')
    rdoc.options << '--all' << '--charset' << 'utf-8'
  end
end
