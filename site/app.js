const languageButton = document.querySelector('#language');
const tutorialLink = document.querySelector('#tutorial-link');
function setLanguage(language) {
  document.documentElement.lang = language;
  document.querySelectorAll('[data-en][data-ko]').forEach(element => {
    // These strings are authored in this page; only the headings contain markup.
    element.innerHTML = element.dataset[language];
  });
  languageButton.textContent = language === 'en' ? '한국어' : 'English';
  languageButton.setAttribute('aria-label', language === 'en' ? 'Switch to Korean' : '영어로 전환');
  tutorialLink.href = language === 'en'
    ? 'lessons/en/index.html'
    : 'lessons/ko/index.html';
  document.title = language === 'en' ? 'Small C++ — Start small. Go further.' : 'Small C++ — 작은 시작. 큰 가능성.';
  document.querySelector('#ide-screenshot').alt = language === 'en'
    ? 'Small C++ desktop IDE with learner code completion, Run and Debug controls, and diagnostics'
    : '학생용 자동완성, 실행과 디버그 도구, 진단 창을 보여 주는 Small C++ IDE';
}
languageButton.addEventListener('click', () => {
  setLanguage(document.documentElement.lang === 'en' ? 'ko' : 'en');
});
document.querySelectorAll('[data-theme]').forEach(button => {
  button.addEventListener('click', () => {
    const screenshot = document.querySelector('#ide-screenshot');
    screenshot.src = `assets/ide-${button.dataset.theme}.png?v=${screenshot.dataset.version}`;
    document.querySelectorAll('[data-theme]').forEach(option => {
      option.setAttribute('aria-pressed', String(option === button));
    });
  });
});
setLanguage('en');
