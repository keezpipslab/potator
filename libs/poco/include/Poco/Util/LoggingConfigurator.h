//
// LoggingConfigurator.h
//
// $Id: //poco/1.4/Util/include/Poco/Util/LoggingConfigurator.h#1 $
//
// Library: Util
// Package: Configuration
// Module:  LoggingConfigurator
//
// Definition of the LoggingConfigurator class.
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
// 
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//


#ifndef Util_LoggingConfigurator_INCLUDED
#define Util_LoggingConfigurator_INCLUDED


#include "Poco/Util/Util.h"
#include "Poco/Formatter.h"
#include "Poco/Channel.h"


namespace Poco {
namespace Util {


class AbstractConfiguration;


class Util_API LoggingConfigurator
	/// This utility class uses a configuration object to configure the
	/// logging subsystem of an application.
	///
	/// The LoggingConfigurator sets up and connects formatters, channels 
	/// and loggers. To accomplish its work, the LoggingConfigurator relies on the
	/// functionality provided by the LoggingFactory und LoggingRegistry classes.
	///
	/// The LoggingConfigurator expects all configuration data to be under a root
	/// property named "logging".
	/// 
	/// Configuring Formatters
	///
	/// A formatter is configured using the "logging.formatters" property. Every 
	/// formatter has an internal name, which is only used for referring to it 
	/// during configuration time. This name becomes part of the property name.
	/// Every formatter has a mandatory "class" property, which specifies the actual
	/// class implementing the formatter. Any other properties are passed on to
	/// the formatter by calling its setProperty() method.
	///
	/// A typical formatter definition looks as follows:
	///     logging.formatters.f1.class = PatternFormatter
	///     logging.formatters.f1.pattern = %s: [%p] %t
	///     logging.formatters.f1.times = UTC
	///
	/// Configuring Channels
	///
	/// A channel is configured using the "logging.channels" property. Like with
	/// Formatters, every channel has an internal name, which is used during
	/// configuration only. The name becomes part of the property name.
	/// Every channel has a mandatory "class" property, which specifies the actual
	/// class implementing the channel. Any other properties are passed on to
	/// the formatter by calling its setProperty() method.
	///
	/// For convenience, the "formatter" property of a channel is treated
	/// specifically. The "formatter" property can either be used to refer to
	/// an already defined formatter, or it can be used to specify an "inline"
	/// formatter definition. In either case, when a "formatter" property is
	/// present, the channel is automatically "wrapped" in a FormattingChannel
	/// object.
	/// 
	/// Similarly, a channel supports also a "pattern" property, which results
	/// in the automatic instantiation of a FormattingChannel object with a
	/// connected PatternFormatter.
	/// 
	/// Examples:
	///     logging.channels.c1.class = ConsoleChannel
	///     logging.channels.c1.formatter = f1
	///     logging.channels.c2.class = FileChannel
	///     logging.channels.c2.path = ${system.tempDir}/sample.log
	///     logging.channels.c2.formatter.class = PatternFormatter
	///     logging.channels.c2.formatter.pattern = %s: [%p] %t
	///     logging.channels.c3.class = ConsoleChannel
	///     logging.channels.c3.pattern = %s: [%p] %t
	///
	/// Configuring Loggers
	///
	/// A logger is configured using the "logging.loggers" property. Like with
	/// channels and formatters, every logger has an internal name, which, however,
	/// is only used to ensure the uniqueness of the property names. Note that this
	/// name is different from the logger's full name, which is used to access
	/// the logger at runtime.
	/// Every logger except the root logger has a mandatory "name" property which
	/// is used to specify the logger's full name.
	/// Furthermore, a "channel" property is supported, which can either refer
	/// to a named channel, or which can contain an inline channel definition.
	///
	/// Examples:
	///     logging.loggers.root.channel = c1
	///     logging.loggers.root.level = warning
	///     logging.loggers.l1.name = logger1
	///     logging.loggers.l1.channel.class = ConsoleChannel
	///     logging.loggers.l1.channel.pattern = %s: [%p] %t
	///     logging.loggers.l1.level = information
{
public:
	LoggingConfigurator();
		/// Creates the LoggingConfigurator.

	~LoggingConfigurator();
		/// Destroys the LoggingConfigurator.
		
	void configure(AbstractConfiguration* pConfig);
		/// Configures the logging subsystem based on
		/// the given configuration.
		///
		/// A ConfigurationView can be used to pass only
		/// a part of a larger configuration.

private:
	void configureFormatters(AbstractConfiguration* pConfig);
	void configureChannels(AbstractConfiguration* pConfig);
	void configureLoggers(AbstractConfiguration* pConfig);
	Poco::Formatter* createFormatter(AbstractConfiguration* pConfig);
	Poco::Channel* createChannel(AbstractConfiguration* pConfig);
	void configureChannel(Channel* pChannel, AbstractConfiguration* pConfig);
	void configureLogger(AbstractConfiguration* pConfig);
	
	LoggingConfigurator(const LoggingConfigurator&);
	LoggingConfigurator& operator = (const LoggingConfigurator&);
};


} } // namespace Poco::Util


#endif // Util_LoggingConfigurator_INCLUDED
