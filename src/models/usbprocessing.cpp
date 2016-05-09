#include "stdafx.h"
#include <cassert>
#include "usbprocessing.h"

namespace {
	int countFileRecursive(QDir d) {
		int tot(0);
		for (auto child : d.entryList(QDir::Dirs)) {
			QDir childDir(d);
			childDir.cd(child);
			tot += countFileRecursive(childDir);
		}
		return tot + d.entryList(QDir::Files).count();
	}
}

class UsbProcessing::Worker {
	UsbProcessing& m_process;
	int m_totalSteps;
	int m_currStep;

public:
	Worker(UsbProcessing& process)
		:m_process(process), m_totalSteps(totSteps())
	{}

	int totSteps() {
		int tot(0);
		if (m_process.m_target.formatFs) {
			tot += 50;
		}
		if (m_process.m_target.templateFolder) {
			tot += countFileRecursive(m_process.m_target.templateFolder.get());
		}
		return tot;
	}

	void format() {

	}

	void copyTemplate() {

	}

	void changeLabel() {

	}

	void run() {
		const auto& t = m_process.m_target;
		if (t.formatFs) {
			format();
		}
		if (t.templateFolder) {
			copyTemplate();
		}
		if (t.label) {
			changeLabel();
		}
	}

};

UsbProcessing::UsbProcessing(UsbDriveInfo drive, QObject* parent)
	:QObject(parent), m_drive(drive), m_state(State::Pending), m_progress(0), m_info(QString())
{}

auto UsbProcessing::process(UsbProcessTarget target) -> std::future<void>
{
	assert(m_state == State::Pending || m_state == State::Finished);
	return std::async(std::launch::async, [&]() {
		Worker worker(*this);
		worker.run();
	});
}

void UsbProcessing::setLetter(QString letter)
{
	if (m_drive.letter != letter) {
		m_drive.letter = letter;
		Q_EMIT sgnLetterChanged(letter);
	}
}

void UsbProcessing::setLabel(QString label)
{
	if (m_drive.label != label) {
		m_drive.label = label;
		Q_EMIT sgnLabelChanged(label);
	}
}

QString UsbProcessing::letter() const
{
	return m_drive.letter;
}

QString UsbProcessing::label() const
{
	return m_drive.label;
}

auto UsbProcessing::state() const -> State
{
	return m_state;
}

int UsbProcessing::progress() const
{
	return m_progress;
}

QString UsbProcessing::info() const
{
	return m_info;
}
