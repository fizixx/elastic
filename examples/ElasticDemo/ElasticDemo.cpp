
#include "canvas/App.h"
#include "elastic/Context.h"
#include "elastic/Renderer/Font.h"
#include "elastic/Views/ColorView.h"
#include "elastic/Views/ImageView.h"
#include "elastic/Views/LabelView.h"
#include "nucleus/FilePath.h"
#include "nucleus/Logging.h"
#include "nucleus/Streams/FileInputStream.h"

class ElasticDemo : public ca::WindowDelegate {
public:
  ElasticDemo() : ca::WindowDelegate("ElasticDemo") {}

  void onWindowResized(const ca::Size& size) override {
    m_context.resize(size);
  }

  bool onWindowCreated(ca::Window* window) override {
    if (!WindowDelegate::onWindowCreated(window)) {
      return false;
    }

    ca::Renderer* renderer = window->getRenderer();

    nu::FileInputStream fontStream(nu::FilePath{"C:\\Windows\\Fonts\\Arial.ttf"});
    if (!fontStream.openedOk()) {
      LOG(Error) << "Could not open font file.";
      return false;
    }

    if (!m_font.load(renderer, &fontStream, 32)) {
      return false;
    }

    if (!m_context.initialize(renderer)) {
      return false;
    }

    auto stackedSizerView = new el::StackedSizerView(&m_context);
    stackedSizerView->setExpansion(el::Expansion::Both);
    m_context.getRootView()->addChild(stackedSizerView);

    auto imageView1 = new el::ImageView(&m_context);
    stackedSizerView->addChild(imageView1);
    imageView1->setMinSize({200, 200});
    imageView1->setExpansion(el::Expansion::Horizontal);

    auto colorView1 = new el::ColorView(&m_context, ca::Color::red);
    stackedSizerView->addChild(colorView1);
    colorView1->setName("colorView1");
    colorView1->setHorizontalAlignment(el::Alignment::Center);
    colorView1->setExpansion(el::Expansion::Vertical);
    colorView1->setMinSize({100, 100});

    auto colorView2 = new el::ColorView(&m_context, ca::Color::blue);
    stackedSizerView->addChild(colorView2);
    colorView2->setName("colorView2");
    colorView2->setHorizontalAlignment(el::Alignment::Center);
    colorView2->setExpansion(el::Expansion::Horizontal);
    colorView2->setMinSize({100, 100});

    auto labelView = new el::LabelView{&m_context, "elastic", &m_font};
    stackedSizerView->addChild(labelView);

    return true;
  }

  void onRender(ca::Renderer* renderer) override {
    m_context.render(renderer);
  }

private:
  DELETE_COPY_AND_MOVE(ElasticDemo);

  el::Context m_context;
  el::Font m_font;
};

CANVAS_APP(ElasticDemo)
